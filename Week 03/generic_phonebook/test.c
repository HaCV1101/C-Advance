#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

SymTable *makeTable(int (*compare)(void*, void*), Entry (*makeNode) (void*, void*))
{
    SymTable *S = (SymTable*)malloc(sizeof(SymTable));
    S->entries = (Entry*)malloc(sizeof(Entry) * INITIAL_SIZE);
    S->size = INITIAL_SIZE;
    S->total = 0;
    S->makeNode = makeNode;
    S->compare = compare;
    return S;
}

void DropTable(SymTable* S)
{
    int n = S->total;
    for(int i = 0; i < n; i++)
    {
        Entry* E = S->entries+i;
        free(E->key);
        free(E->value);
    }
    S->total = 0;
}

Entry* Search(void* key, SymTable* S)
{
    int n = S->total;
    //if(n == 0) return NULL;
    for(int i = 0; i < n; i++)
    {
        //printf("%d", i);
        Entry* E = S->entries + i;
        int x = S->compare(E->key, key);
        if(x == 0) return E;
    }
    return NULL;
}

void addEntry(void* key, void* value, SymTable* S)
{
    Entry *X = Search(key, S);
    if(X != NULL)
    {
        X->value = value;
        return;
    }
    int n = S->total;
    printf("%d %d", n, S->size);
    if(n >= S->size)
    {

        S->size += INCREMENTAL_SIZE;
        S->entries = realloc(S->entries, sizeof(Entry)* S->size);
    }
    //printf("d");
    //Entry E = S->makeNode(key, value);
//    S->entries[n].key = key;
//    S->entries[n].value = value;
//    Entry E = S->makeNode(key, value);
//    //printf("%s %ld\n", (char*)E.key, E.value);
    S->entries[n] = S->makeNode(key, value);
//    printf("%s %d\n", S->entries[n].key, S->entries[n].value);
    //S->makeNode(key,value);
    S->total++;
    return;
}

void Print(SymTable* S)
{
    int n = S->total;
    for(int i = 0; i < n; i++)
    {
        Entry* E = S->entries + i;
        //printf("%d\n", i);
        printf("%s %d\n", E->key, E->value);
    }
}
