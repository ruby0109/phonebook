#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
/* mmap for size of file*/
#include <sys/stat.h>
/* mmap*/
#include <sys/mman.h>
#include <sys/types.h>
/* This is for open. */
#include <fcntl.h>

#include IMPL

#define POOL_SIZE 400000
#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

#if defined(THRD)
    int j, pagesize;
    struct stat file_status;
    unsigned long int bytes_left=0;

    mmap_arg *Pmmap;
    Pmmap = (mmap_arg *)malloc(sizeof(mmap_arg));
    Pmmap->bytes_read=0;
    Pmmap->to_read=0;

    /* Initial pthread*/
    void *status;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);


    /* create a memory pool and initialize hash table*/
    hash_ptr = Initial();
    /* open the file*/
    Pmmap->fd = open(DICT_FILE,O_RDONLY);
    /* check the size of the file*/
    fstat(Pmmap->fd, &file_status);
    /* check the size of page for mmap to asign virtual address space*/
    pagesize = getpagesize();
    bytes_left = file_status.st_size;

    /* clean cache*/
#if defined(__GNUC__)
    __builtin___clear_cache((char *) hash_ptr, (char *) hash_ptr + HASH_SIZE*sizeof(HashTable));
#endif

    /* if remain data bigger that pagesize, then just give pagesize data to mmap*/
    clock_gettime(CLOCK_REALTIME, &start);
    while(bytes_left > 0) {
        if (bytes_left > pagesize) {
            Pmmap->to_read = pagesize;
        } else {
            Pmmap->to_read = bytes_left;
        }
        for(i=0; i<NUMTHRDS; i++) {
            pthread_create(&thrd[i], &attr, pmmap, (void *)Pmmap);
        }
        pthread_attr_destroy(&attr);

        /* Wait on the other threads */
        for(i=0; i<NUMTHRDS; i++) {
            pthread_join(thrd[i], &status);
        }

        j=0;
        for(i=0; i<Pmmap->to_read; i++) {
            line[j] = Pmmap->data[i];
            j++;
            if(Pmmap->data[i] == '\n') {
                line[j-1]='\0';
                assert(append(line, hash_ptr) && "Not enough space" );
                j = 0;
            }
        }

        munmap(Pmmap->data, Pmmap->to_read);
        Pmmap->bytes_read += Pmmap->to_read;
        bytes_left -= Pmmap->to_read;

    }


#else
    /* check file opening */
    FILE *fp;
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#if defined(HASH)

    /* the analysis of hash function's distribution*/
#if defined(SLOT)
    int hash_slot[HASH_SIZE]= {0};
#endif

    HashTable *hash_ptr;
    hash_ptr = Initial_HashTable();

#elif defined(POOL)

    /* create a memory pool and initialize hash table*/
    hash_ptr = Initial();

#else
    /* build the entry */
    entry *pHead, *e;
    printf("size of entry : %lu bytes\n", sizeof(entry));
    pHead = (entry *) malloc(sizeof(entry));
    e = pHead;
    e->pNext = NULL;
#endif


#if defined(HASH)

    /* clean cache*/
#if defined(__GNUC__)
    __builtin___clear_cache((char *) hash_ptr, (char *) hash_ptr + HASH_SIZE*sizeof(HashTable));
#endif

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
#if defined(SLOT)
        hash_slot[HashFunction(line)]++;
#endif
        append(line,hash_ptr);
    }

#elif defined(POOL)
    /* clean cache*/
#if defined(__GNUC__)
    __builtin___clear_cache((char *) record, (char *) record + HASH_SIZE*sizeof(entry));
#endif

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;

        assert(append(line, hash_ptr) && "Not enough space" );

    }
#else
#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
    }
#endif
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

#if defined(THRD)
#else
    /* close file as soon as possible */
    fclose(fp);
#endif

#if defined(HASH)
    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    assert(findName(input,hash_ptr) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input,hash_ptr)->lastName, "zyxel"));

    /* clean cache*/
#if defined(__GNUC__)
    __builtin___clear_cache((char *) hash_ptr, (char *) hash_ptr + HASH_SIZE*sizeof(HashTable));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input,hash_ptr);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

#if defined(SLOT)
    FILE *output2;
    output2 = fopen("slot.txt","a");
    for( i=0; i<HASH_SIZE; i++) {
        fprintf(output2, "%d %d\n",i,hash_slot[i]);
    }
    fclose(output2);
#endif

#elif defined(POOL) || defined(THRD)
    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    assert(findName(input,hash_ptr) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, hash_ptr)->lastName, "zyxel"));

    /* Clean Cache*/
#if defined(__GNUC__)
    __builtin___clear_cache((char *) record, (char *) record + HASH_SIZE*sizeof(entry));
#endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input,hash_ptr);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

#else
    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    e = pHead;
    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
#endif

    FILE *output;
#if defined(OPT)
    output = fopen("opt.txt", "a");
#elif defined(HASH)
    output = fopen("hash.txt", "a");
#elif defined(POOL)
    output = fopen("memory.txt","a");
#elif defined(THRD)
    output = fopen("thread.txt","a");
#else
    output = fopen("orig.txt", "a");
#endif

    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);
#if defined(POOL)
    return 0;
#elif defined(THRD)
    pthread_exit(NULL);
#elif defined(HASH)
    free(hash_ptr);
#else
    if (pHead->pNext) free(pHead->pNext);
    free(pHead);
#endif
    return 0;
}
