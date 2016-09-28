#include <stdlib.h>
#include <string.h>//strcasecmp function
#include <stdio.h>
#include <ctype.h>
#include "phonebook_hash.h"

entry *findName(char lastname[], HashTable *hash_ptr)
{
    entry* list;
    int value;
    value = HashFunction(lastname);

    for (list=hash_ptr->tail[value]; list->pNext != NULL ; list=list->pNext) {
        if (strcasecmp(lastname, list->lastName) == 0) {
            return list;
        }
    }
    return NULL;
}

/* allocate memory for the new entry and put lastName*/
void append(char lastName[], HashTable *hash_ptr)
{
    entry *e;
    e = (entry *) malloc(sizeof(entry));
    int value;
    value = HashFunction(lastName);
    strcpy(e->lastName, lastName);

    e->pNext=hash_ptr->tail[value];
    hash_ptr->tail[value]=e;

}
/*
// APHash
unsigned int HashFunction(char *str)
{
    unsigned int hash = 0;
    int i;

    for (i=0; *str; i++) {
        if ((i & 1) == 0) {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        } else {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }
    return (hash & HASH_SIZE);
}
*/
/*
// BKDR Hash Function
unsigned int HashFunction(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & HASH_SIZE);
}
*/

//djb2 Hash Function
unsigned int HashFunction(char *str)
{
    unsigned int hash = 5381;
    int c;

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return (hash & HASH_SIZE);
}

/* allocate space for the Hash Table structure*/
HashTable *Initial_HashTable(void)
{

    hash_ptr = (HashTable* )malloc(sizeof(HashTable));
    hash_ptr->tail = malloc(HASH_SIZE*sizeof(entry*));
    int i;
    for(i=0; i<HASH_SIZE; i++) {
        hash_ptr->tail[i]=NULL;
    }
    return hash_ptr;

}





















