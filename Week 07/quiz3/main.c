#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graph.h"

int Maxx;

char station[150][150];
int line[150][150];


void printV(int v) {printf("%4d", v);}




void input(Graph G)
{
    FILE* inp = fopen("inp.txt", "r");
    if(inp == NULL) 
    {
        printf("-1\n");
        return;
    }
    printf("111\n");
    char tmp[80];
    int d = 0;
    while(fgets(tmp, 80, inp) != NULL)
    {
        int n = strlen(tmp);
        tmp[n - 1] = '\0';
        if(strcmp(tmp, "[STATIONS]") == 0) 
        {
            d = 1;
            continue;
        }
        if(strcmp(tmp, "[LINES]") == 0)
        {
            d = 2;
            continue;
        }
        int i = 0;
        
        if(d == 1)
        {
            int x = tmp[1] - '0';
            strcpy(station[x], tmp + 3);
            //printf("%s\n", station[x]);
        }
        if(d == 2)
        {
            int x = tmp[1] - '0';
            int dem  = 0;
            printf("line %d: ", x);
            for(int i = 4; i < n ; i+=3)
            {
                dem++;
                line[x][dem] = tmp[i] -'0';
                printf("%d ", tmp[i] - '0');
            }printf("\n");
            for(int i = 1; i < dem; i++)
            {
                for(int j = i + 1; j <= dem; j++)
                {
                    addEdge(G, line[x][i], line[x][j]);
                }
            }
        }
    }
}

int main()
{
    Graph G = create();
    input(G);
    // adjacent(G, 1);
    // printf("\n");
    printf("BFS: from node 1 to 4: ");
    BFS(G, 1, 4, printV);
    printf("\nBFS: from node 1 to all:");
    BFS(G, 1, -1, printV);
}