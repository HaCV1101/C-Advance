#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"

int makeInt(char* X)
{
    int res = 0;
    for(int i = 0; i < strlen(X); i++)
    {
        res = res * 10 + (X[i] - '0');
    }
    return res;
}

void input(Graph* G, char* filename)
{
    FILE* inp = fopen(filename, "r");
    char tmp[50];
    while (fgets(tmp, 50, inp) != NULL)
    {
        int i = 0, j;
        char in1[20], in2[20];
        tmp[strlen(tmp) - 1] = '\0';
        //printf("%s\n", tmp);
        while (tmp[i] == ' ') i++; j = i;
        while (tmp[j] != ' ')
        {
            in1[j - i] = tmp[j];
            j++;
        }in1[j] = '\0';  i = j;
        while (tmp[i] == ' ') i++; j = i;
        while (tmp[j] != ' ')
        {
            in2[j - i] = tmp[j];
            j++;
        }in2[j] = '\0'; 
        int a = makeInt(in1);
        int b = makeInt(in2);
        //printf("%d %d\n", a, b);
        add(G, a, b);
    }
    fclose(inp);
}

int main()
{
    int n, out[100];
    Graph *G = create(Maxx);
    char filename[30];
    FILE* inpp = fopen("inp.txt", "r");
    while (1)
    {
        fscanf(inpp,"%s", filename);
        printf("%s\n", filename);
        if( strcmp(filename, "-1") == 0) break;
        input(G, filename);
    }
    fclose(inpp);
    for(int i = 0; i <= G->maxnode; i++)
    {
        n = getAdjacent(G, i, out);
        if (n==0) printf("No adjacent vertices of node %d\n", i);
        else {
        printf("Adjacent of node %d: ", i);
        for (int j=0; j<n; j++) {printf("%d ", out[j]);
        out[j] = 0;}
        printf("\n");
        }
    }
}