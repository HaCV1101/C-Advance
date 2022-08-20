#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "jrb.h"
#include "dllist.h"

typedef enum{false, true} bool;
typedef JRB Graph;
typedef Dllist Queue;
typedef Dllist Stack;

Graph create();
void addVertex(Graph G, int id, char* name);
char* getVertex(Graph G, int id);
void addEdge(Graph G, int v1, int v2);
int hasEdge(Graph G, int v1, int v2);
int indegree(Graph G, int v, int* output);
int outdegree(Graph G, int v, int* output);
int adjacent(Graph G, int v1);
void dropGraph(Graph G);

void BFS(Graph G, int s, int f, void (*func)(int));
int DAG(Graph G);



#endif