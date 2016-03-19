#include <stdlib.h>
#include <string.h>//strcasecmp function
#include <stdio.h>//printf
#include <ctype.h>
#include "phonebook_opt.h"

entry* HashHead[ 0x7FFFF];

entry *findName(char lastname[], entry *pHead)
{
    entry* e = HashHead[key(lastname)];

    while (e->pNext != NULL) {
        if (strcasecmp(lastname, e->lastName) == 0) {
            return e;
        }
        e = e->pNext;
    }
    //printf(" %12s  is found!\n", lastName);why error?
    return NULL;
}

/* allocate memory for the new entry and put lastName*/
entry *append(char lastName[], entry *e)
{
    e = (entry *) malloc(sizeof(entry)); //buffer
    e->pNext=NULL;
    strcpy(e->lastName, lastName); 
    if(HashHead[key(lastName)] != NULL){
	e->pNext = HashHead[key(lastName)];
        HashHead[key(lastName)]=e;
    }
    else{
        HashHead[key(lastName)]=e; 
    }

    return e;
}

// APHash
unsigned int key(char *str)
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

    return (hash & 0x7FFFFFFF);
}
//hashvalue of the hash table
//int Hashfunction(int key){
  //  key = key % 42737;
    //return key;
//}









