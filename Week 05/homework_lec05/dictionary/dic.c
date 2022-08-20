#include<stdlib.h>
#include<string.h>
#include "dic.h"

const int INCREMENTAL_SIZE = 10;
const int INITIAL_SIZE = 30;

// list* create()
// {
//     list* L = (list*)malloc(INITIAL_SIZE* sizeof(list));
// }

Dic* initial(char* filename)
{
    BTA* X;
    btinit();
    X = btcrt(filename,0,0);
    return X;
}

char* Search(Dic* D, char* key)
{
    char *val = (char*)malloc(MaxLength);
    int l;
    if(btsel(D, key, val, MaxLength, &l) == 0) return val;
    else return "-1";
}

void add(Dic* D, char* key, char* val)
{
    char* X = Search(D, key);
    //printf("dd\n");
    if(strcmp(X, "-1") != 0) btupd(D, key, val, MaxLength);
    else btins(D, key, val, MaxLength);
}

void delete(Dic* D, char* key)
{   
    char* X = Search(D, key);
    if(strcmp(X, "-1") != 0) btdel(D, key);
    else printf("Word not found\n");
}

void freeList(Dic* D)
{
    char key[ZKYLEN+1];
    char val[ZKYLEN+1];
    int l;
    btpos(D, ZSTART);
    while(btseln(D, key, val, MaxLength, &l) == 0) btdel(D, key);
    return;
}

BTA* FindSub(Dic* D, char* word, int* Maxx)
{
    *Maxx = 0;
    BTA* now;
    now = initial("tmp_db");
    char key[ZKYLEN+1];
    char val[ZKYLEN+1];
    int l;
    btpos(D, ZSTART);
    while(btseln(D, key, val, MaxLength, &l) )
    {
        //printf("%s\n", key);
        char* X = strstr(key, word);
        printf("%c\n", *X);
        if(*X == word[0]) {add(now, key, val); *Maxx++;}
    }
}


void Print(Dic* D)
{
    char key[ZKYLEN+1];
    char val[ZKYLEN+1];
    int l;
    btpos(D, ZSTART);
    while(btseln(D, key, val, MaxLength, &l) == 0)
        printf("%s: %s\n", key ,val);
}

list* run(Dic* D, int m)
{
    list *L = (list*)malloc(m * sizeof(list));
    int i = 1;
    char key[ZKYLEN+1];
    char val[ZKYLEN+1];
    int l;
    btpos(D, ZSTART);
    while(btseln(D, key, val, MaxLength, &l) == 0)
    {
        strcpy((L + i )->A, key);
        strcpy((L + i )->B, val);
    }
    return L;
}