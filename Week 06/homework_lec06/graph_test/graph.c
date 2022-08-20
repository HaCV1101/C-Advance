#include<stdio.h>
#include<stdlib.h>
#include "graph.h"

int change(int v1, int v2, int size)
{
    return v1 * size + v2;
}

// void back(int v, int size, int* x, int* y)
// {
//     *x = v / size;
//     *y = v % size;
//     return; 
// }

Graph *create(int size)
{
    Graph *G = (Graph*)malloc(sizeof(Graph));
    G->Node = (int*)calloc(size * size + size, sizeof(int));
    G->Maxsize = size;
    G->maxnode = 0;
    return G;
}
void add(Graph *G, int v1, int v2)
{
    int n = G->Maxsize;
    if(G->maxnode < v1) G->maxnode = v1;
    if(G->maxnode < v2) G->maxnode = v2;
    G->Node[change(v1, v2, n)] = G->Node[change(v2, v1, n)] = 1;
    return;
}

int adjacent(Graph *G, int v1, int v2)
{
    int n = G->Maxsize;
    return G->Node[change(v1, v2, n)];
}

int getAdjacent(Graph *G, int v, int* out)
{
    int n = G->Maxsize;
    //out = (int*) malloc(n * sizeof(int));
    int count = 0;
    for(int i = 0; i <= G->maxnode; i++)
    {
        if(G->Node[change(v, i, n)] == 1) 
        {
            out[count] = i;
            count++;
        }
    }
    return count;
}

void dropGraph(Graph* G)
{
    int n = G->Maxsize;
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++)
            (G->Node + i)[j] = 0;
}