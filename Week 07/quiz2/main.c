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
    printf("DFS: from node 1 to 4: ");
    DFS(G, 1, 4, printV);
    printf("\nDFS: from node 1 to all:");
    DFS(G, 1, -1, printV);
}