#include<stdio.h>
#include<stdlib.h>
#include "graph.h"


Graph *create()
{
    Graph* G = make_jrb();
    return G;
}
void add(Graph *G, int v1, int v2)
{
    JRB tree;
    JRB node1 = jrb_find_int(G, v1);
    if(node1 == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(G, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node1->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }

    JRB node2 = jrb_find_int(G, v2);
    if(node2 == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(G, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node2->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}

int getAdjacent(Graph *G, int v, int* output)
{
    JRB node = jrb_find_int(G, v);
    if(node == NULL) return 0;
    JRB tree = (JRB) jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree)
    output[++total] = jval_i(node->key);
    return total;
}

void dropGraph(Graph* G)
{
    JRB node, graph;
    graph = G;
    jrb_traverse(node, graph)
    jrb_free_tree( jval_v(node->val) );
}