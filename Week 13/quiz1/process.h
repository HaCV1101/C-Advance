#ifndef __PROCESS_H__
#define __PROCESS_H__

#include<stdlib.h>
#include<stdio.h>
#include"jrb.h"

typedef JRB checkStat;

typedef struct trThai
{
    int s[10][10];
    trThai* prev;
    trThai* next;
}trThai;

//typedef struct trThai trThai;


typedef struct Queue
{
    trThai* first;
    int size;
}Queue;

Queue* makeQueue();
void enqueue(Queue* Q, trThai* now);
void dequeue(Queue* Q);

int check(trThai* stat1, trThai* stat2);
//void process(Queue* Q, trThai* goal, int pointer);

checkStat create();
int putStat(checkStat C, char* stat);
void initial(checkStat C);

#endif