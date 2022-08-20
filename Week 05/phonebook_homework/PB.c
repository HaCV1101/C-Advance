#include <stdio.h>
#include <stdlib.h>
#include "PB.h"

const int oo = 1e9;

PB* initial()
{
    PB* P;
    btinit();
    P = btcrt("test_db", 0, FALSE);
    return P;
}


BTint search(BTA* root, char* key)
{
    BTint a;
    int X = bfndky(root, key, &a);
    if(X != 0) return -1;
    else  return a;
}


void* addNode(PB* P, char* key, BTint val)
{
    BTint X = search(P, key);
    printf("%d\n", X);
    if(X != -1) bupdky(P, key, val);
    else binsky(P, key, val);
}


void* Delete(PB* P, char* key)
{
    BTint X = search(P, key);
    if(X != -1) printf("%d\n", bdelky(P, key) );
    else printf("Key not exist\n");
}