#include <stdlib.h>
#include <string.h>//strcasecmp function
#include <stdio.h>//printf
#include <ctype.h>
#include <assert.h>
#include <pthread.h>
#include "phonebook_thread.h"

/* record the address in memory pool*/
entry *record,*end;

entry *findName(char lastname[])
{
    entry* list;
    int value;
    value = HashFunction(lastname);

    for (list=hash_ptr->tail[value];list!= NULL ; list=list->pNext) {
        if (strcasecmp(lastname, list->lastName) == 0) {
            return list;
        }
    }
    return NULL;
}

/* allocate memory for the new entry and put lastName*/
int append(char lastName[])
{
    entry *e;

    e = palloc();

    if (e == NULL) return 0; 
 
    int value;
    value = HashFunction(lastName);
    strcpy(e->lastName, lastName);

    e->pNext=hash_ptr->tail[value];
    hash_ptr->tail[value]=e;

    return 1;
}

/* djb2 Hash Function */
unsigned int HashFunction(char *str)
{
    unsigned int hash = 5381;
    int c;

    while((c = *str++)){
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
/* Initial hash table and memory pool*/
void Initial(void){

    record = (entry* )malloc(POOL_SIZE *sizeof(entry));

    hash_ptr = (HashTable* )malloc(sizeof(HashTable));
    hash_ptr->tail = malloc(HASH_SIZE*sizeof(entry*));
    int i;
    for(i=0;i<HASH_SIZE;i++){
        hash_ptr->tail[i]=NULL;
    }
    
    end = record + POOL_SIZE;
}

/*  return the memory space at once */                               
void pool_destroy( entry *record){                                                   
    free(record);                                                                   
}                                                                              

/*  each time alloc a entry size memory */
entry *palloc (void){                                       
    
if (((int64_t *)end > (int64_t *)(record+32))){
        record = record+ 1;
        return (record);
    }
    return NULL;  
                                                       
}                                                                              


/* Optimal 4*/
/* threads*/
void Append(void *fp){

    char line[16];
    int i;

    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;

        assert(append(line) && "Not enough space" );

    }
    pthread_exit(NULL);

}







