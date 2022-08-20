#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "phonebook.h"


PhoneBook* createPhoneBook() {
    PhoneBook* A = (PhoneBook*)malloc(sizeof(PhoneBook));
    A->total = 0;
    A->size = INITIAL_SIZE ;
    A->entries = (PhoneEntry*)malloc(INITIAL_SIZE*sizeof(PhoneEntry));
    return A;
}

void dropPhoneBook(PhoneBook* book) {
    free(book->entries);
    book->size = 0;
    book->total = 0;
}

void addPhoneNumber(char * name, long number, PhoneBook* book) {
    book->total++;
    int size = book->total;
    if(size > book->size) {
        book->size += INCREMENTAL_SIZE;
        book->entries = (PhoneEntry*)realloc(book->entries,sizeof(PhoneEntry) * (book->size));
    }
    PhoneEntry* now = (book->entries) + size;
    //printf(("%p\n",now));
    now->number = number;
    strcpy(now->name,name);
    return;
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook *book) {
    int n = book->total;
    for(int i = 1; i <= n; i++)
    {
        PhoneEntry* X = (book->entries) + i;
        if(strcmp(X->name,name) == 0) return X;
    }
    return NULL;
}