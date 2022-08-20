#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "dllist.h"

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL) // only add new vertex
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}
char *removeVertex(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL)
        return NULL;
    else
    {
        char *val = jval_s(node->val);
        jrb_delete_node(node);
        return jval_s(node->val);
    }
}

Dllist getAllEdges(Graph g)
{
    //A dllist of unique edges
    Graph usedEdges = createGraph();
    JRB child, father;
    double *entry;
    int f, c;
    Dllist list = new_dllist();
    jrb_traverse(father, g.edges)
        jrb_traverse(child, ((JRB)jval_v(father->val)))
    {
        f = jval_i(father->key);
        c = jval_i(child->key);
        if (getEdgeValue(usedEdges, c, f) == oo)
        {
            addEdge(usedEdges, f, c, 1);
            entry = malloc(sizeof(double[3]));
            entry[0] = getEdgeValue(g, f, c);
            entry[1] = (double)f;
            entry[2] = (double)c;
            dll_append(list, new_jval_v(entry));
        }
    }
    dropGraph(usedEdges);
    return list;
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == oo)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

int removeEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return 0;
    else
    {
        jrb_delete_node(node);
        return 1;
    }
}

double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return oo;
    tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return oo;
    else
        return jval_d(node->val);
}

int setEdgeValue(Graph graph, int v1, int v2, double val)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return 0;
    else
    {
        node->val = new_jval_d(val);
        return 1;
    }
}

int remove_duplicate(int arr[], int n)
{
    if (n == 0 || n == 1)
        return n;

    int *temp = malloc(sizeof(int) * n);

    int j = 0;
    int i;
    for (i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];
    temp[j++] = arr[n - 1];

    for (i = 0; i < j; i++)
        arr[i] = temp[i];
    free(temp);
    return j;
}

int getAdjacentVertices(Graph g, int v, int *output)
{
    int inn, outn;
    inn = indegree(g, v, output);
    outn = outdegree(g, v, output + inn);
    return remove_duplicate(output, inn + outn);
}

int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

void BFS(Graph graph, int start, int stop, void (*func)(int))
{
    int *visited = malloc(sizeof(int) * 10000);
    memset(visited, 0, sizeof(int) * 10000);
    int n, output[10000], i, u, v;
    Dllist node, queue;

    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);

        if (!visited[u])
        {
            func(u);
            visited[u] = 1;
            if (u == stop)
            {
                free(visited);
                return;
            }
            n = outdegree(graph, u, output);
            for (i = 0; i < n; i++)
            {
                v = output[i];

                if (!visited[v])
                    dll_append(queue, new_jval_i(v));
            }
        }
    }
    free(visited);
}

void DFS(Graph graph, int start, int stop, void (*func)(int))
{
    int *visited = malloc(sizeof(int) * 10000);
    memset(visited, 0, sizeof(int) * 10000);
    int n, output[100], i, u, v;
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
            func(u);
            visited[u] = 1;
            if (u == stop)
            {
                free(visited);
                return;
            }
            n = outdegree(graph, u, output);
            for (i = 0; i < n; i++)
            {
                v = output[i];
                if (!visited[v])
                    dll_append(stack, new_jval_i(v));
            }
        }
    }
    free(visited);
}

int UAGUtil(Graph g, int v, int visited[], int parent)
{
    // Mark the current node as visited
    visited[v] = 1;

    // Recur for all the vertices
    // adjacent to this vertex
    int output[100];
    int n = outdegree(g, v, output);
    for (int i = 0; i < n; ++i)
    {
        // If an adjacent vertex is not visited,
        //then recur for that adjacent
        if (!visited[output[i]])
        {
            if (UAGUtil(g, output[i], visited, v))
                return 1;
        }

        // If an adjacent vertex is visited and
        // is not parent of current vertex,
        // then there exists a cycle in the graph.
        else if (output[i] != parent)
            return 1;
    }
    return 0;
}

// Returns true if the graph contains
// a cycle, else false.
int UAG(Graph g)
{
    JRB node;
    // Mark all the vertices as not
    // visited and not part of recursion
    // stack
    int *visited = malloc(sizeof(int) * 10000);
    memset(visited, 0, sizeof(int) * 10000);

    // Call the recursive helper
    // function to detect cycle in different
    // DFS trees
    jrb_traverse(node, g.vertices)
    {
        if (!visited[node->key.i])
        {
            if (UAGUtil(g, node->key.i, visited, -1))
            {
                free(visited);
                return 1;
            }
        }
    }
    free(visited);
    return 0;
}

int DAG(Graph graph)
{
    int *visited = malloc(sizeof(int) * 10000);
    int n, output[100], i, u, v, start;
    Dllist node, stack;
    JRB vertex;

    jrb_traverse(vertex, graph.vertices)
    {
        memset(visited, 0, sizeof(int) * 10000);

        start = jval_i(vertex->key);
        stack = new_dllist();
        dll_append(stack, new_jval_i(start));

        while (!dll_empty(stack))
        {
            node = dll_last(stack);
            u = jval_i(node->val);
            dll_delete_node(node);
            if (!visited[u])
            {
                visited[u] = 1;
                n = outdegree(graph, u, output);
                for (i = 0; i < n; i++)
                {
                    v = output[i];
                    if (v == start)
                    { // cycle detected
                        free(visited);
                        return u;
                    }
                    if (!visited[v])
                        dll_append(stack, new_jval_i(v));
                }
            }
        }
    }
    free(visited);
    return -1; // no cycle
}

void inDegArr(Graph g, int *arr)
{
    int out[1000];
    JRB node, tree = g.vertices;
    jrb_traverse(node, tree)
    {
        int key = jval_i(node->key);
        arr[key] = indegree(g, key, out);
    }
}

void topologicalSort(Graph g, int *out, int *n)
{
    Dllist node, queue;
    JRB vertex;
    queue = new_dllist();
    *n = 0;
    int o[1000];
    int *indega = malloc(sizeof(int) * 10000);
    memset(indega, 0, sizeof(int) * 10000);
    inDegArr(g, indega);
    jrb_traverse(vertex, g.vertices)
    {
        if (indega[jval_i(vertex->key)] == 0)
            dll_append(queue, vertex->key);
    }
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        int v = jval_i(node->val);
        dll_delete_node(node);
        out[(*n)++] = v;
        int n = outdegree(g, v, o);
        for (int i = 0; i < n; ++i)
        {
            indega[o[i]]--;
            if (indega[o[i]] == 0)
                dll_append(queue, new_jval_i(o[i]));
        }
    }
    free(indega);
}
/*
double dijkstra(Graph g, int s, int t, int* path, int* length)
{
   double* distance = malloc(sizeof(double) * 10000), min, w, total;
   int* previous = malloc(sizeof(double) * 20000), 
   *tmp = previous + 10000;
   int n, output[100], i, u, v, start;
   Dllist ptr, queue, node;

   for (i=0; i<10000; i++)
       distance[i] = oo;
   distance[s] = 0;
   previous[s] = s;
       
   queue = new_dllist();
   dll_append(queue, new_jval_i(s));

   while ( !dll_empty(queue) )
   {
      // get u from the priority queue   
      min = oo;   
      dll_traverse(ptr, queue)
      {
          u = jval_i(ptr->val);              
          if (min > distance[u])
          {
             min = distance[u];
             node = ptr;
          }                 
      }
      u = jval_i(node->val);
      dll_delete_node(node);
      
      if (u == t) break; // stop at t
      
      n = outdegree(g, u, output);
      for (i=0; i<n; i++)
      {
          v = output[i];
          w = getEdgeValue(g, u, v);
          if ( distance[v] > distance[u] + w )
          {    
              distance[v] = distance[u] + w;
              previous[v] = u;
          }     
          dll_append(queue, new_jval_i(v));
      }
   }
   total = distance[t]; 
   if (total != oo)
   {
       tmp[0] = t;
       n = 1;              
       while (t != s)
       {
             t = previous[t];
             tmp[n++] = t;
       }
       for (i=n-1; i>=0; i--)
           path[n-i-1] = tmp[i];
       *length = n;                
   }
   free(distance);
   free(previous);
   return total;   
}
*/

double dijkstra(Graph g, int s, int t, int *path, int *length)
{
    double *d = malloc(10000 * sizeof(double)), min, w, total; //khoang cach tu diem dau
    for (int i = 0; i < 10000; i++)
    {
        d[i] = oo;
    }
    d[s] = 0;
    int *diemtruoc = (int *)malloc(10000 * sizeof(int));
    int *check = (int *)calloc(10000, sizeof(int)); //visited
    Dllist queue = new_dllist(), node, ptr;
    dll_append(queue, new_jval_i(s));
    int u, v;
    int n;
    int output[1000];
    JRB tmp, tmp1, tmp2;
    while (!dll_empty(queue))
    {
        min = oo;
        dll_traverse(ptr, queue)
        {
            u = jval_i(ptr->val);
            if (min > d[u])
            {
                min = d[u];
                node = ptr;
            }
        }
        u = jval_i(node->val);
        dll_delete_node(node);

        if (u == t)
            break;

        n = outdegree(g, u, output);
        tmp = jrb_find_int(g.edges, u);
        if (check[u] == 0)
        {
            for (int i = 0; i < n; i++)
            {
                v = output[i];
                w = getEdgeValue(g, u, v);
                dll_append(queue, new_jval_i(output[i]));
                if (d[output[i]] == 1000)
                {
                    d[v] = w + d[u];
                    diemtruoc[v] = u;
                }
                else if (w + d[u] < d[v])
                {
                    d[v] = w + d[u];
                    diemtruoc[v] = u;
                }
            }
        }
        check[u] = 1;
    }
    total = d[t];
    if (total != oo)
    {
        int arr[100];
        int x = 0;
        int m = t;
        while (m != s)
        {
            arr[x++] = m;
            m = diemtruoc[m];
        }
        arr[x++] = s;
        *length = 0;
        for (int i = x - 1; i >= 0; i--)
        {
            path[(*length)++] = arr[i];
            printf("%s ", getVertex(g, arr[i]));
        }
    }
    return total;
}

double bellmanford(Graph g, int s, int t, int *path, int *length)
{
    double *distance = malloc(sizeof(double) * 10000);
    for (int i = 0; i < 10000; ++i)
        distance[i] = oo;
    int *predecessor = malloc(sizeof(int) * 20000), *tmp = predecessor + 10000;
    memset(predecessor, 0, sizeof(int) * 20000);
    double total;
    int out[100];
    int i, j;
    int u, v, w;
    int v_num, n;
    JRB vertex, edge;

    //for(i = 0; i < 1000; i++)
    //   distance[i] = oo;
    distance[s] = 0;

    v_num = 0;
    jrb_traverse(vertex, g.vertices)
        v_num++;

    for (i = 0; i < (v_num - 1); ++i)
        for (u = 0; u < v_num; ++u)
        {
            n = outdegree(g, u, out);
            for (j = 0; j < n; ++j)
            {
                v = out[j];
                w = getEdgeValue(g, u, v);
                if (distance[v] > distance[u] + w)
                {
                    distance[v] = distance[u] + w;
                    predecessor[v] = u;
                }
            }
        }

    for (u = 0; u < v_num; ++u)
    {
        n = outdegree(g, u, out);
        for (j = 0; j < n; ++j)
        {
            v = out[j];
            w = getEdgeValue(g, u, v);
            if (distance[v] > distance[u] + w)
            {
                printf("Graph contains a negative-weight cycle.\n");
                *length = -1;
                return -1;
            }
        }
    }
    total = distance[t];
    if (total != oo)
    {
        tmp[0] = t;
        n = 1;
        while (t != s)
        {
            t = predecessor[t];
            tmp[n++] = t;
        }
        for (i = n - 1; i >= 0; i--)
            path[n - i - 1] = tmp[i];
        *length = n;
    }
    free(distance);
    free(predecessor);
    return total;
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}
int graphColoring(Graph g, int *result)
{
    JRB node;
    result[0] = 0;
    int v_num, total, output[100];
    jrb_traverse(node, g.vertices)
        v_num++;

    for (int i = 1; i < v_num; i++)
        result[i] = -1;

    int *available = calloc(v_num, sizeof(int));

    for (int i = 1; i < v_num; i++)
    {
        total = getAdjacentVertices(g, i, output);
        for (int j = 0; j < total; j++)
        {
            int adj = output[j];

            if (result[adj] != -1)
                available[result[adj]] = 1;
        }

        int cl = 0;
        for (; cl < v_num; cl++)
            if (available[cl] == 0)
                break;

        result[i] = cl;

        for (int j = 0; j < total; j++)
        {
            int adj = output[j];

            if (result[adj] != -1)
                available[result[adj]] = 0;
        }
    }

    free(available);
    return v_num;
}
