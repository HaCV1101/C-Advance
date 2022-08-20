#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

bool visited[500];

Graph create()
{
    Graph G;
    G = make_jrb();
    return G;
}

Stack createS()
{
    Stack S = new_dllist();
    return S;
}

void put(Stack S, int v)
{
    dll_prepend(S, new_jval_i(v));
    return;
}

int adjacent(Graph G, int v1)
{
    JRB node = jrb_find_int(G, v1);
    JRB tree = (JRB)jval_v(node->val);
    jrb_traverse(node, tree)
    {
        printf("%4d", jval_i(node->key));
    }
}

void addEdge(Graph G, int v1, int v2)
{
    //printf("%d %d\n", v1, v2);
    JRB node, tree;
    node = jrb_find_int(G, v1);
    if(node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(G, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }

    node = jrb_find_int(G, v2);
    if(node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(G, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
    // adjacent(G, v1);
    // printf("\n");
    // adjacent(G, v2);
    // printf("\n");
}


void freeGraph(Graph G)
{
    JRB node, graph;
    graph = G;
    jrb_traverse(node, graph)
    jrb_free_tree( jval_v(node->val) );
}

void reset()
{
    for(int i = 0; i <= 100; i++) visited[i] = false;
}

void DFS(Graph G, int s, int f, void (*func)(int))
{
    reset();
    Stack S = createS();
    visited[s] = true;
    put(S, s);
    while(!dll_empty(S))
    {
        Dllist now = dll_last(S);
        int v = jval_i(now->val);
        dll_delete_node(now);
        JRB node = jrb_find_int(G, v);
        if(node == NULL) {printf("b");return;}
        JRB tree = (JRB) jval_v(node->val);
        jrb_traverse(node, tree)
        {
            int u = jval_i(node->key);
            if(visited[u] == true) continue;
            visited[u] = true;
            put(S, u);
            func(u);
            if(u == f) 
            {
                while(!dll_empty(S)) dll_delete_node(dll_first(S));
                break;
            }
        }
    }
}