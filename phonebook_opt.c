#include <stdlib.h>
#include <string.h>//strcasecmp function
#include <stdio.h>//printf
#include <ctype.h>
#include "phonebook_opt.h"
 
entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0){
            //printf(" %12s  is found!\n", lastName);
            return pHead;
        }
        pHead = pHead->pNext;
    }
    //printf(" %12s  is found!\n", lastName);why error?
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

// AP Hash Function  
unsigned int APHash(char *str)  
{  
    unsigned int hash = 0;  
    int i;  
   
    for (i=0; *str; i++)  
    {  
        if ((i & 1) == 0)  
        {  
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));  
        }  
        else  
        {  
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));  
        }  
    }  
   
    return (hash & 0x7FFFFFFF);  
} 

