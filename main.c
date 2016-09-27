#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

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
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;
    /* record the size of pool*/
    int space = POOL_SIZE;
    printf("\n origin space %d\n",space);

    /* the analysis of hash function's distribution*/
#if defined(SLOT)
    int hash_slot[HASH_SIZE]= {0};
#endif

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }
#if defined(HASH)

    /* the analysis of hash function's distribution*/
    #if defined(SLOT)
    int hash_slot[HASH_SIZE]={0};
    #endif

    HashTable *hash_ptr;
    Initial_HashTable();

#elif defined(POOL) || defined(THREAD)

    /* create a memory pool and initialize hash table*/
    Initial();

#else    
    /* build the entry */
    entry *pHead, *e;
    printf("size of entry : %lu bytes\n", sizeof(entry));
    pHead = (entry *) malloc(sizeof(entry));
    e = pHead;
    e->pNext = NULL;
#endif


#if defined(HASH)

    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
    #if defined(SLOT)
        hash_slot[HashFunction(line)]++;
    #endif
        append(line);
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
     
        assert(append(line) && "Not enough space" );
        
    }
#elif defined(THREAD)
/* clean cache*/
    #if defined(__GNUC__)                                                      
        __builtin___clear_cache((char *) record, (char *) record + HASH_SIZE*sizeof(entry));
    #endif
    /* Append with threads */
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    void *status;

    pthread_attr_init(&attr);
    
    clock_gettime(CLOCK_REALTIME, &start);

    for(i=0; i<NUM_THREADS; i++) {
        rc = pthread_create(&thread[i], &attr, (void *)Append, fp);  
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_attr_destroy(&attr);
    for(i=0; i<NUM_THREADS; i++) {
       rc = pthread_join(thread[i], &status);
       if (rc) {
          printf("ERROR; return code from pthread_join() is %d\n", rc);
          exit(-1);
          }
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

    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);
#if defined(HASH)
    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    assert(findName(input) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input)->lastName, "zyxel"));

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    #if defined(SLOT)
    FILE *output2;
    output2 = fopen("slot.txt","a");
    for( i=0;i<HASH_SIZE;i++){
        fprintf(output2, "%d %d\n",i,hash_slot[i]);
    }
    fclose(output2);
    #endif    

#elif defined(POOL) || defined(THREAD)
    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    assert(findName(input) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input)->lastName, "zyxel"));

    /* Clean Cache*/
    #if defined(__GNUC__)                                                      
        __builtin___clear_cache((char *) record, (char *) record + HASH_SIZE*sizeof(entry));
    #endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input);
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
#elif defined(THREAD)
    output = fopen("thread.txt","a");
#else
    output = fopen("orig.txt", "a");
#endif

    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);
#if defined(POOL) || defined(HASH) 
    return 0;
#elif  defined(THREAD)
    pthread_exit(NULL);
    return 0;
#else
    if (pHead->pNext) free(pHead->pNext);
    free(pHead);
#endif
    return 0;
}
