#include <stdlib.h>
#include <string.h>//strcasecmp function
#include <stdio.h>//printf
#include <ctype.h>
#include "phonebook_memory.h"

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
    return NULL;
}

/* allocate memory for the new entry and put lastName*/
entry *append(char lastName[], entry *e)
{
    e = palloc(e);
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
/* APHash
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
/* BKDR Hash Function
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

/* djb2 Hash Function */
unsigned int HashFunction(char *str)
{
    unsigned int hash = 5381;
    int c;

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return (hash & HASH_SIZE);
}

/*  Optimal 3*/
/*  memory pool*/
/*
 *  This code now only can alloc memory for last name structure(entry)
 *  and use another integer to record the remain memory of pool.
 *
*/
/*  First use malloc to alloc a pool of memory( size+sizeof POOL),
    p->next is the first node in POOL */
entry *pool_create( size_t size )
{

    entry *p = (entry*)malloc((size*sizeof(entry)));
    return p;
}
/*  return the memory space at once */
void pool_destroy( entry *p)
{
    free(p);
}

/*  each time alloc a entry size memory */
entry *palloc (entry *p)
{

    return (++p);

}




