#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16


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

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif


