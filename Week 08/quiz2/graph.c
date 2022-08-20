#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

int visited[500];

void nothing(int x)
{
    return;
}

Graph create()
{
    Graph G;
    G = make_jrb();
    return G;
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

void addVertex(Graph G, int id, char* name)
{
    //char* now = getVertex(G, id);
    //if(now == NULL) 
    //{
        JRB tree = make_jrb();
        jrb_insert_int(G, id, new_jval_v(tree));
        return;
    //}
}

char* getVertex(Graph G, int id)
{
    JRB node;
    node = jrb_find_int(G, id);
    return jval_s(node->val);
}

int hasEdge(Graph G, int v1, int v2)
{
    JRB node = jrb_find_int(G, v1);
    JRB tree = (JRB)jval_v(node->val);
    JRB check = jrb_find_int(tree, v2);
    if(check != NULL) return 1;
    else return 0;
}

void addEdge(Graph G, int v1, int v2)
{
    //printf("%d %d\n", v1, v2);
    JRB node = jrb_find_int(G, v1);
    JRB tree = (JRB)jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_i(1));
    // adjacent(G, v1);
    // printf("\n");
    // adjacent(G, v2);
    // printf("\n");
}

int indegree(Graph G, int v, int* output)
{
    int dem = 0;
    JRB node, graph;
    graph = G;
    jrb_traverse(node, graph)
    {
        int u = jval_i(node->key);
        if(u == v) continue;
        if(hasEdge(G, u, v) == 1) 
            //{output[dem] = u; 
            dem++;
            //}
    }
    return dem;
}

int outdegree(Graph G, int v, int* output)
{
    int dem = 0;
    JRB node = jrb_find_int(G, v);
    JRB tree = (JRB)jval_v(node->val);
    JRB now;
    jrb_traverse(now, tree)
    {
        int u = jval_i(node->key);
        //output[dem] = u; dem++;
    }
    return dem;
}


void dropGraph(Graph G)
{
    JRB node, graph;
    graph = G;
    jrb_traverse(node, graph)
    jrb_free_tree( jval_v(node->val) );
}

void reset()
{
    for(int i = 0; i <= 100; i++) visited[i] = 0;
}

void BFS(Graph G, int s, int f, void (*func)(int))
{
    if(s >= 0) reset();
    else s = -s;
    //visited[s] = 1;
    Queue Q = new_dllist();
    addQueue(Q, s);
    while(!dll_empty(Q))
    {
        Dllist now = dll_first(Q);
        int v = jval_i(now->val);
        dll_delete_node(now);
        //printf("\n--- %d ---\n",v);
        visited[v] = 2;
        if(v == f) break;
        JRB node = jrb_find_int(G, v);
        if(node == NULL) {printf("b");continue;}
        JRB tree = (JRB) jval_v(node->val);
        jrb_traverse(node, tree)
        {
            int u = jval_i(node->key);
            //func(u);
            if(visited[u] > 0)
            {
                if(visited[u] == 2) visited[u]++;
                continue;
            }
            visited[u] = 1;
            func(u);
            if(u == f) break;
            dll_append(Q, new_jval_i(u));
        }
    }
}


/////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////

int DAG(Graph G)
{
    reset();
    int d = 0;
    JRB node, graph;
    graph = G;
    jrb_traverse(node, graph)
    {
        int u = jval_i(node->key);
        if(visited[u] > 0) continue;
        BFS(G, -u, -1, nothing);
        //printf("------run %4d: --------\n", u);
        if(visited[u] == 3) {d = 1; break;}
    }
    return d;
}


int checkIn(Graph G, int u)
{
    int output[100];
    if(indegree(G, u, &output) == 0)
    {

    }

}


void topoSort(Graph G, int* out, int *n)
{
    Stack S = createS();
    JRB node, graph;
    graph = G;
    int output[100];
    jrb_traverse(node, graph);
    {
        int u = jval_i(node->val);
        if(indegree(G, u, &output) == 0)
        {
            dll_prepend(S, new_jval_i(u));
            break;
        }
    }
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