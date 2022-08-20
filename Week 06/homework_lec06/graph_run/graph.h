#ifndef __GRAPH_H__
#define __GRAPH_H__

#include"jrb.h"

#define Maxx 100

typedef JRB Graph;

Graph *create();
void add(Graph *G, int v1, int v2);
int adjacent(Graph *G, int v1, int v2);
int getAdjacent(Graph *G, int v, int* output);
void dropGraph(Graph *G);




#endif