#include <stdlib.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0){
            printf(" %12s  is found!\n", lastName);
            return pHead;
        }
        pHead = pHead->pNext;
    }
    printf(" %12s  is found!\n", lastName);
    return NULL;
}

entry *append(char lastName[], entry *ape)
{
    /* allocate memory for the new entry and put lastName */
    ape->pNext = (lastNameEntry *) malloc(sizeof(lastNameEntry));
    ape = ape->pNext;
    strcpy(ape->lastName, lastName);
    ape->pNext = NULL;

    return ape;
}
