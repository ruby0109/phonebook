#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_SIZE 42737
<<<<<<< HEAD
#define POOL_SIZE 400000
=======
>>>>>>> 2f7ccdb7bde3ee4ba27d7158fa471375fe8e7dab

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

<<<<<<< HEAD
=======

>>>>>>> 2f7ccdb7bde3ee4ba27d7158fa471375fe8e7dab
detail *findNameDetail(char lastname[], detail *pHead);
detail *appendDetail(char lastName[], detail *e);

/*Optimal 3*/
/* Memory Pool*/
typedef struct __POOL {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *data;//data pointer to detail struct
<<<<<<< HEAD
    struct __POOL *pNext;// the address of next point 
} entry;

entry *findName(char lastname[]);
int append(char lastName[]);

/* Hash Table*/
unsigned int HashFunction(char *str);

/* record the tail of each buckets*/
typedef struct __HASH_TABLE {
    entry **tail;
}HashTable;

HashTable *hash_ptr;                                                             
/* Initial hash table and memory pool*/
void Initial(void);
/*  return the memory space at once */
void pool_destroy( entry *p);
/*  each time alloc a entry size memory */
entry *palloc (void);
/* record the address in memory pool*/
entry *record,*end;
=======
    struct __POOL *pNext;// the address of next point
} entry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

/*Optimal 2*/
/* Hash Table*/
unsigned int HashFunction(char *str);


/*  First use malloc to alloc a pool of memory( size+sizeof POOL),
    p->next is the first node in POOL */
entry *pool_create( size_t size );
void pool_destroy( entry *p);
entry *palloc (entry *p);
>>>>>>> 2f7ccdb7bde3ee4ba27d7158fa471375fe8e7dab

#endif


