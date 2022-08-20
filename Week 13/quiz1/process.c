#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "process.h"
#include "jrb.h"
#include "dllist.h"


Queue* makeQueue()
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->size = 0;
    Q->first = NULL;
    return Q;
}

void enqueue(Queue* Q, trThai* now)
{
    if(Q->size == 0)
    {
        Q->first = now;
        //now->next = NULL;
        Q->size++;
        return;
    }
    trThai* run = Q->first;
    while(run->next != NULL) run = run->next;
    run->next = now;
    Q->size++;
}

void dequeue(Queue* Q)
{
    trThai* first = Q->first;
    Q->first = first->next;
    free(first);
    Q->size--;
}



int check(trThai* stat1, trThai* stat2)
{
    int d = 1;
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++)
            if(stat1->s[i][j] != stat2->s[i][j])
            {
                d = 0;
                break;
            }
        if(d == 0) break;
    }
    return d;
}

checkStat create()
{
    JRB m = make_jrb();
    return m;
}

int putStat(checkStat C, char* stat)
{
    JRB node = jrb_find_str(C, stat);
    if(node != NULL) return 0;
    jrb_insert_str(C, strdup(stat), new_jval_i(1));
    return 1;
}

int checking(checkStat C, trThai* now){
    char tmp[15];
    strcpy(tmp,"");
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            int x = now->s[i][j];
            strcat(tmp, (char)x);
        }
    }
    return putStat(C, tmp);
}

void swap(int * x, int *y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void process(Queue* Q, char* goal, checkStat C)
{
    int d = 0;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};
    int status[10][10];
    trThai *finish;
    while (Q->size != 0) {
        trThai* now = Q->first;
        int x, y;
        for(int i = 1; i <= 3; i++)
            for(int j = 1; j <= 3; j++) {
                status[i][j] = now->s[i][j];
                if(status[i][j] == 0){
                    x = i;
                    y = j;
                }
            }
        for(int i = 0; i < 4; i++) {
            // int y = pointer % 3;
            // int x = pointer / 3 + 1;
            int xx = x + dx[i];
            int yy = y + dy[i];
            if(xx <= 0 || xx > 3 || yy <= 0 || yy > 3) continue;
            swap(&status[x][y], &status[xx][yy]);
            trThai * New = (trThai*)malloc(sizeof(trThai));
            New->next = NULL;
            New->prev = NULL;
            char tmp[15];
            strcpy(tmp,"");
            for(int i = 1; i <= 3; i++)
                for(int j = 1; j <= 3; j++) {
                    int x = status[i][j];
                    New->s[i][j] = x;
                    strcat(tmp, (char)x);
                }

            if(strcmp(tmp, goal) == 0) {
                New->prev = now;
                finish = New;
                d = 1;
                break;
            }

            if(putStat(C, tmp) == 0) {
                swap(&status[x][y], &status[xx][yy]);
                continue;
            }
            else {
                New->prev = now;
                enqueue(Q, New);
            }
        }
        if(d == 1) break;
    }


}

void initial(checkStat C)
{
    Queue* Q = makeQueue();
    int status[10][10];
    int d[10];
    for(int i = 0; i <= 8; i++) d[i] = 0;
    int pointer;
    char tmp[15];
    strcpy(tmp,"");
    trThai * New = (trThai*)malloc(sizeof(trThai));
    New->next = NULL;
    New->prev = NULL;
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            int x = rand() % 8 + 1;
            while (d[x] == 1)   x = rand() % 9;
            New->s[i][j] = x;
            if(x == 0) pointer = (i - 1) * 3 + j;
            strcat(tmp, (char)x);
            printf("%d ",x);
        }
        printf("\n");
    }
    enqueue(Q, New);
    printf("%s\n", tmp);
    char goal[10];
    strcpy(goal,"123456780");
    // trThai* goal = (trThai*)malloc(sizeof(trThai));
    // for(int i = 1; i <= 3; i++)
    // {
    //     for(int j = 1; j <= 2; j++)
    //     {
    //         goal->s[i][j] = (i - 1) * 3 + j;
    //     }
    // }
    // goal->s[3][3] = 0;
    process(Q, goal, C);
}