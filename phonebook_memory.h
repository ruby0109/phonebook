#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define HASH_SIZE 42737

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

/*Optimal 3*/
/* Memory Pool*/
typedef struct __POOL {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *data;//data pointer to detail struct
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

#endif



