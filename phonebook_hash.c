#include <stdlib.h>
#include <string.h>//strcasecmp function
#include <stdio.h>//printf
#include <ctype.h>
#include "phonebook_hash.h"

entry *HashHead[HASH_SIZE], *Hashe[HASH_SIZE];//Hash record the positionof the linked list

entry *findName(char lastname[], entry *pHead)
{
    int i;
    i = HashFunction(lastname);

    while (HashHead[i] != NULL) {
        if (strcasecmp(lastname, HashHead[i]->lastName) == 0) {
            return HashHead[i];
        }
        HashHead[i] = HashHead[i]->pNext;
    }
    //printf(" %12s  is found!\n", lastName);why error?
    return NULL;
}

/* allocate memory for the new entry and put lastName*/
entry *append(char lastName[], entry *e)
{
    e = (entry *) malloc(sizeof(entry)); //buffer
    int i;
    i = HashFunction(lastName);
    strcpy(e->lastName, lastName);

    if(HashHead[i] == NULL) {
        HashHead[i] = e;
        Hashe[i]=HashHead[i];
        Hashe[i]->pNext=NULL;
    } else {
        Hashe[i]->pNext = e;
        Hashe[i]=Hashe[i]->pNext;
        Hashe[i]->pNext=NULL;
    }
    return e;
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

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash & HASH_SIZE);
}





