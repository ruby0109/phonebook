#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_SIZE 42737
#define POOL_SIZE 400000
#define NUMTHRDS 2

typedef struct __PHONE_BOOK_DETAIL {
    //char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_DETAIL*dNext;
} detail;

detail *findNameDetail(char lastname[], detail *pHead);
detail *appendDetail(char lastName[], detail *e);

/* Memory Pool*/
typedef struct __POOL {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *data;//data pointer to detail struct
    struct __POOL *pNext;// the address of next point
} entry;

/* record the tail of each buckets*/
typedef struct __HASH_TABLE {
    entry **tail;
} HashTable;

HashTable *hash_ptr;

/* Hash Table*/
unsigned int HashFunction(char *str);

entry *findName(char lastname[], HashTable *hash_ptr);
int append(char lastName[], HashTable *hash_ptr);

/* Initial hash table and memory pool*/
HashTable *Initial(void);
/*  return the memory space at once */
void pool_destroy( entry *p);
/*  each time alloc a entry size memory */
entry *palloc (void);
/* record the address in memory pool*/
entry *record,*end;

/* thread */
void *pmmap(void* ptr);

typedef struct __MMAP_ARG {
    unsigned long int bytes_read;
    unsigned long int to_read;
    int fd;
    char *data;
} mmap_arg;

mmap_arg *Pmmap;
pthread_mutex_t mutex1;
pthread_t thrd[NUMTHRDS];

#endif



