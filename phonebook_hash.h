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

/*Optimal 1*/
//shrink the struct to lastname
typedef struct __LAST_NAME__ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *data;//data pointer to detail struct
    struct __LAST_NAME__ENTRY *pNext;// the address of next point value
} entry;

/*Optimal 2*/
unsigned int HashFunction(char *str);

/* record the tail of each buckets*/
typedef struct __HASH_TABLE {
    entry **tail;
} HashTable;

HashTable *hash_ptr;
HashTable* Initial_HashTable(void);

entry *findName(char lastname[], HashTable *hash_ptr);
void append(char lastName[], HashTable *hash_ptr);


#endif


