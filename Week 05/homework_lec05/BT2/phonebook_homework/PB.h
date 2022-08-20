#ifndef __PB_H_
#define __PB_H__

#include"btree.h"

typedef BTA PB;

PB* initial();
void* addNode(PB* P, char* key, BTint val);
BTint search(PB* P, char* key);
void* Delete(PB* P, char* key);

#endif