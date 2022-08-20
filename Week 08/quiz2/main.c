#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

int Maxx;

void printV(int v) {printf("%4d", v);}

void input(Graph G)
{
    FILE* inp = fopen("inp.txt", "r");
    if(inp == NULL) 
    {
        printf("-1\n");
        return;
    }
    int n;
    fscanf(inp, "%d", &n);
    printf("%d\n", n);
    for(int i = 1 ; i <= n; i++)
    {
        int u, v;
        fscanf(inp,"%d %d", &u, &v);
        addVertex(G, u, u);
        addVertex(G, v, v);
        if(u > Maxx) Maxx = u;
        if(v > Maxx) Maxx = v;
        printf("%d %d\n", u, v);
        addEdge(G, u, v);
    }
    fclose(inp);
}

int main()
{
    Graph G = create();
    printf("1\n");
    input(G);
    // adjacent(G, 1);
    // printf("\n");
    printf("BFS: from node 1 to 4: \n");
    BFS(G, 1, 4, printV);
    printf("\nBFS: from node 1 to all: \n");
    BFS(G, 1, -1, printV);
    printf("\n");
    if(DAG(G) == 1) printf("\nHave cycles in graph\n");
    else printf("\nThe graph is acycle\n");
}