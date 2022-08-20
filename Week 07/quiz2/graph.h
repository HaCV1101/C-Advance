#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "jrb.h"
#include "dllist.h"

typedef enum{false, true} bool;
typedef JRB Graph;
typedef Dllist Stack;

Graph create();
void addEdge(Graph G, int v1, int v2);
int adjacent(Graph G, int v1);

Stack createS();
void put(Stack S, int v);
void DFS(Graph G, int s, int f, void (*func)(int));



#endif