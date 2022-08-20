#include<stdio.h>
#include<stdlib.h>
#include "graph.h"

#define newline printf("\n") 
int maxxNode;

int findMax(int x, int y)
{
    if(x > y) return x;
    else return y;
}

void input(char* filename, Graph* G)
{
    FILE* inp = fopen(filename,"r");
    if(inp == NULL) {
        printf("file not exist\n");return;
    }
    int n;
    fscanf(inp,"%d", &n);
    int x,y;
    for(int i = 1; i <= n; i++)
    {
        fscanf(inp,"%d%d", &x, &y);
        //printf("%d %d\n", x, y);
        maxxNode = findMax(findMax(x,y), maxxNode);
        add(G, x, y);
    }
    fclose(inp);

}

int main()
{
    Graph *G = create();
    input("inp.txt",G);
    printf("Max node is %d\n", maxxNode);
    int output[5 * maxxNode];
    for(int i = 1; i <= maxxNode; i++)
    {
        int total = getAdjacent(G, i, &output);
        printf("%d have %d adjacent(s): ", i, total);
        for(int j = 1; j <= total; j++)
        {
            printf("%d ",output[j]);
        }newline;
    }
}