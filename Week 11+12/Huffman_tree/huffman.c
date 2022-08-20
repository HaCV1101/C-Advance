#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

double INFINITY = 1e10;

HuffmanTree *create()
{
    HuffmanTree* H = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    H->Tree = make_jrb();
    return H;
}


void count(HuffmanTree* H, char tmp)
{
    JRB Tree = H->Tree;
    JRB node;
    //if(tmp[i] == '\n') break;
    char c[2];
    c[0] = tmp;
    c[1] = '\0';
    //printf("%d %s\n",i, c);
    node = jrb_find_str(Tree, c);
    if(node == NULL)
        jrb_insert_str(Tree, strdup(c), new_jval_i(1));
    else {
        int u = jval_i(node->val);
        // char s[10];
        // strcpy(s, jval_s(node->key));
        jrb_delete_node(node);
        jrb_insert_str(Tree, strdup(c), new_jval_i(u + 1));
    }
    
    //return Tree;
}


Queue* make()
{
    Queue *Q;
    Q = (Queue*)malloc(sizeof(Q));
    Q->size = 0;
    return Q;
}

void enqueue(Queue* Q, Node* X)
{
    char key[5];
    strcpy(key,X->key);
    int val = X->val;
    //printf("%3s %3d             ////////////////////////////////////////////////////////\n", key, val);
    X->next = NULL;
    if(Q->size == 0)  {
        X->next = NULL;
        Q->first = X;
        Q->size++;
        return;
    }
    else {
        Node *run = Q->first; 
        //printf("size  = %d\n", Q->size);
        int i = 1, prev = 0, next = 0;
        Node* prevPos = run;
        while(1) {
            //if() break;
            if(i == 1) {
                if(val <= run->val) {
                    X->next = run;
                    Q->first = X;
                    Q->size++;
                    break;
                }
            }
            if(i == Q->size) {
                run->next = X;
                Q->size++;
                break;
            }
            prev = run->val;
            next = run->next->val;
            //printf("prev: %d; next: %d\n", prev,next);
            if(val >= prev && val < next) {
                X->next = run->next;
                run->next = X;
                Q->size++;
                break;
            }
            else {
                //prev = run->val;
                run = run->next;
                i++;
            }
        }
    }
}


void dequeue(Queue* Q)
{
    Node* first = Q->first;
    Q->first = first->next;
    free(first);
    Q->size--;
    return;
}


Node* makeNode(char* key, int val)
{
    Node* X = (Node*)malloc(sizeof(Node));
    X->left = NULL;
    X->right = NULL;
    X->next = NULL;
    strcpy(X->key, key);
    X->val = val;
    return X;
}

Node* coppy(Node*A)
{
    Node* X = (Node*)malloc(sizeof(Node));
    strcpy(X->key, A->key);
    X->val = A->val;
    X->left = A->left;    X->right = A->right;    X->next = A->next;
    return X;
}


Node* addTree(Node* first, Node* second)
{
    Node* left = coppy(first);
    Node* right = coppy(second);
    Node* X = makeNode("-1", left->val + right->val);
    X->left = left;   X->right = right;
    return X;
}



void process(HuffmanTree* H)
{
    JRB Tree = H->Tree;
    Queue* Q = make();
    JRB node;
    jrb_traverse(node, Tree) {
        //printf("ddd\n");
        char key[5];
        strcpy(key, jval_s(node->key));
        int val = jval_i(node->val); //printf("%4s %d\n", key, val);
        enqueue(Q, makeNode(key, val));
    }
    while(Q->size != 0)
    {
        Node* first = coppy(Q->first);
        //printf("%s %4d   +  ", first->key, first->val);
        dequeue(Q);
        if(Q->size == 0) 
        {
            H->root = coppy(first);
            free(Q);
            break;
        }
        Node* second = coppy(Q->first);
        //printf("%s %4d   =  ", second->key, second->val);
        dequeue(Q);
        Node* root = addTree(first, second);
        enqueue(Q, root);
    }
}

// void print(Node* root)
// {
    
// }

