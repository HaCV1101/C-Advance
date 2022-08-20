#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
int *dumpArray(int *p, int size)
{
    int *a;
    // int *a = (int *)malloc(size * sizeof(int));
    memcpy(a, p, size);
}
void main()
{
    int *a, *b;
    int c[MAX] = {};
    int d[MAX] = {1, 2, 3,4,5,6,7,8,9,0};
    //printf("%s\n%s\n", c, d);
    // for (int i = 0; i < MAX; i++)
    // {
    //     printf("%2d", c[i]);
    // }
    printf("\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("%2d", d[i]);
    }
    printf("\n");
    memcpy(c, d, MAX * sizeof(int));
    for (int i = 0; i < MAX; i++)
    {
        printf("%2d", c[i]);
    }
    printf("\n");
    //printf("%s\n", c);
    // a = (int *)malloc(MAX * sizeof(int));
    // srand((unsigned)clock());
    // for (int i = 0; i < MAX; i++)
    // {
    //     a[i] = rand() % 11;
    //     printf("%5d", a[i]);
    // }
    // printf("\n");
    // memcpy(b, a, MAX);
    // printf("Mang b :\n");
    // for (int i = 0; i < MAX; i++)
    // {

    //     printf("%5d", b[i]);
    // }
    // printf("\n");
    // free(a);
    //free(b);
}