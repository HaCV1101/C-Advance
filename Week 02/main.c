#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 30
int *creatNewArray(int size)
{
    int *a = (int *)calloc(size, sizeof(int)); //tao mang dong a voi SIZE phan tu
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 10 + 1; //tao ra so ngau nhien trong khoang 1-10
    }
    return a;
}
void *memcpy(void *region1, const void *region2, size_t n)
{
    const char *first = (const char *)region2;
    const char *last = ((const char *)region2) + n;
    char *result = (char *)region1;
    while (first != last)
        *result++ = *first++;
    return result;
}
int compare(void const *x, void const *y)
{
    int m, n;
    m = *((int *)x);
    n = *((int *)y);
    if (m == n)
        return 0;
    return m > n ? 1 : -1;
}
void exch(void *buf, int size, int i, int j)
{
    void *temp = (void *)malloc(size);
    memcpy(temp, (char *)buf + i * size, size);
    memcpy((char *)buf + i * size, (char *)buf + j * size, size);
    memcpy((char *)buf + j * size, temp, size);
    free(temp);
}
void sort(void *a, int size, int left, int right, int (*compare)(void const *, void const *))
{
    if (right <= left)
        return;
    int i = left - 1, j = right;
    int p = left - 1, q = right;
    while (1)
    {
        while (compare((char *)a + (++i) * size, (char *)a + right * size) < 0)
            ;
        while (compare((char *)a + right * size, (char *)a + (--j) * size) < 0)
            if (i == j)
                break;
        if (i >= j)
            break;
        exch(a, size, i, j);
        if (compare((char *)a + j * size, (char *)a + right * size) == 0)
            exch(a, size, ++p, i);
        if (compare((char *)a + j * size, (char *)a + right * size) == 0)
            exch(a, size, --q, j);
    }
    exch(a, size, i, right);
    j = i - 1;
    i = i + 1;
    for (int k = left; k <= p; k++)
        exch(a, size, k, j--);
    for (int k = right - 1; k >= q; k--)
        exch(a, size, k, i++);
    sort(a, size, left, j, compare);
    sort(a, size, i, right, compare);
}
int main()
{
    int *a = creatNewArray(SIZE);
    sort(a, sizeof(int), 0, SIZE - 1, compare);
    for (int i = 0; i < SIZE; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");
    return 0;
}