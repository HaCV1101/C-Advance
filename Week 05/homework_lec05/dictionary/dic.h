#ifndef __DIC_H__
#define __DIC_H__
#include "btree.h"

#define MaxLength 30
typedef BTA Dic;

typedef struct 
{
    char A[30];
    char B[30];
}list;



Dic* initial(char* filename);
char* Search(Dic* D, char* key);
void add(Dic* D, char* key, char* val);
void delete(Dic* D, char* key);
BTA* FindSub(Dic* D, char* key, int *Maxx);

void Print(Dic* D);
list* run(Dic* D, int m);


#endif