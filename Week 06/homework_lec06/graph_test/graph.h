#ifndef __GRAPH_H__
#define __GRAPH_H__

#define Maxx 100

typedef struct 
{
    int *Node;
    int Maxsize;
    int maxnode;
}Graph;

Graph *create(int size);
void add(Graph *G, int v1, int v2);
int adjacent(Graph *G, int v1, int v2);
int getAdjacent(Graph *G, int v, int* out);
void dropGraph(Graph *G);




#endif