#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "graph.h"

double oo = 1e10;

void printNode(int key)
{
    printf("%4d", key);
}


char* change(int x)
{
    char tmp[20];
    int l = 0;
    if(x == 0)
    {
        tmp[0] = '0';
        tmp[1] = '\0';
        return strdup(tmp);
    }
    while(x != 0)
    {
        int y = x % 10;
        tmp[l] = y + '0';
        l++;
        x = x / 10;
    }
    tmp[l] = '\0';
    for(int i = 0; i < l / 2; i++)
    {
        char a;
        a = tmp[i];
        tmp[i] = tmp[l - i - 1];
        tmp[l - i - 1] = a;
    }
    printf("%s\n", tmp);
    return strdup(tmp);
}


void input(Graph G)
{
    FILE* inp = fopen("inp.txt", "r");
    if(inp == NULL)
    {
        printf("Can't open file\n");
        return;
    }
    int n;
    fscanf(inp, "%d", &n);
    printf("%d\n",n);
    for(int i = 1; i <= n; i++)
    {
        int u, v;
        float w;
        fscanf(inp, "%d %d %f", &u, &v, &w);
        //printf("%d %d %f\n", u, v, w);
        addVertex(G, u, change(u));
        addVertex(G, v, change(v));
        addEdge(G, u, v, w);   /// do thi co huong
        //addEdge(G, v, u, w); 
    }
    fclose(inp);
}

int main()
{
    Graph g = createGraph();
    input(g);
    //addEdge(g, 4, 1);
    DFS(g, 0, -1, printNode);
    printf("\n");

    if (isDAG(g))
        printf("This is a DAG!\n");
    else
        printf("This is not a DAG!\n");
        
    int out[1000];
    int length = 0;
    float weight = ShortestPath(g, 0, 5, out, &length);
    printf("%d\n", length);
    if(weight == oo) printf("There is no path.\n");
    else
        for (int i = length; i >= 1; i--)
            printf("%4d", out[i]);
}
