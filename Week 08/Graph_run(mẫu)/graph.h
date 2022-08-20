#ifndef __GRAPH_H__
#define __GRAPH_H__
#include<stdio.h>
#include<stdlib.h>
#include "jrb.h"
#include "dllist.h"


typedef struct {
    JRB vertices;
    JRB edges;
} Graph;


typedef struct Path
{
  float d;
  int node;
  struct Path* next;
}Path; //////////////

typedef struct 
{
  Path* first;
  int size;
}Queue; /////////////


Graph createGraph();
void addVertex(Graph g, int id, char *name);
void addEdge(Graph g, int v1, int v2, float weight);

char *getVertexName(Graph g, int id);
int getVertexId(Graph g, char *name);

int hasEdge(Graph g, int v1, int v2);

Dllist incomingVertices(Graph g, int v);
Dllist outgoingVertices(Graph g, int v);

void dropGraph(Graph g);

void BFS(Graph g, int source, int dest, void (*f)(int key));
void DFS(Graph g, int source, int dest, void (*f)(int key));
int isDAG(Graph g);

float ShortestPath(Graph G, int s, int f, int* out, int* length);


#endif
  
