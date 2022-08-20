#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include<stdio.h>
#include<stdlib.h>
#include "jrb.h"
#include "dllist.h"



typedef struct  Node
{
    struct Node* left;
    struct Node* right;
    struct Node* next;
    char key[2];
    int val;
    int pos;
}Node;

typedef struct Element
{
    Node* val;
    struct Element* next;
}Element;


typedef struct {
    JRB Tree;
    Node* root;
    int height;
}HuffmanTree;



typedef struct 
{
    Node* first;
    int size;
}Queue;

Queue* make();
void enqueue(Queue* Q, Node* X);
void dequeue(Queue* Q);

Node* makeNode(char *key, int val);





HuffmanTree *create();
void count(HuffmanTree *H, char tmp);
void process(HuffmanTree* H);
//void print(Node* root);


#endif