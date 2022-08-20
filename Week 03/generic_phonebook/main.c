#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "test.h"

typedef long long ll;

int *int_compare(void* x, void* y)
{
    ll a = *((ll*)x);
    ll b = *((ll*)y);
    if(x == y) return 0;
    return 1;
}

int *string_compare(void* x, void* y)
{
    return strcmp((char*)x,(char*)y);
}

int *real_compare(void* x, void* y)
{
    double a = *((double*)x);
    double b = *((double*)y);
    if(x == y) return 0;
    return 1;
}

Entry makeNode(void *name, void* phone)
{
    Entry E;// = (Entry*)malloc(sizeof(Entry));
    //printf("%d %d\n", sizeof(name), sizeof(phone));
    E.key = strdup((char*)name);
    printf("dd");
    E.value = (long*)malloc(sizeof(long));
    E.value = (long)phone;
    printf("%s %ld\n", E.key, E.value);
    return E;
}

int main()
{
    SymTable* S = makeTable(string_compare, makeNode);
    addEntry("AAAA", 12345670, S);
    addEntry("BBAD", 85631296, S);
    addEntry("CCdE", 98765432, S);
    addEntry("AAAA", 25836914, S);
    printf("a\n");
    Print(S);
    Entry *E = Search("AAAA", S);
    printf("%d", E->value);
    return 0;
}
