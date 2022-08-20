#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 40
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
int *dumpArray(int *a, int size)
{
    int *p = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++)
    {
        p[i] = a[i];
    }
    return p;
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
        if (compare((char *)a + i * size, (char *)a + right * size) == 0)
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
void swap(void *n1, void *n2, int size)
{
    void *temp = (void *)malloc(size);
    memcpy(temp, n1, size);
    memcpy(n1, n2, size);
    memcpy(n2, temp, size);
    free(temp);
}
int partition(void *arr, int size, int low, int high)
{
    void *pivot;
    pivot = (char *)arr + high * size; // pivot
    int i = (low - 1);                 // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if ((char *)arr + j * size < (char *)pivot)
        {
            i++; // increment index of smaller element
            swap((char *)arr + i * size, (char *)arr + j * size, size);
        }
    }
    swap((char *)arr + (i + 1) * size, (char *)arr + high * size, size);
    return (i + 1);
}
void quickSort(void *arr, int size, int low, int high, int (*partition)(void *, int, int, int))
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, size, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, size, low, pi - 1, partition);
        quickSort(arr, size, pi + 1, high, partition);
    }
}
int main()
{
    int *a = creatNewArray(SIZE);
    int *b = dumpArray(a, SIZE);
    clock_t start, end, start1, end1;
    float time_use, time_use1;
    start = clock();
    sort(a, sizeof(int), 0, SIZE - 1, compare);
    end = clock();
    time_use = (float)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime for 3_way_partition: %f", time_use);
    start1 = clock();
    quickSort(b, sizeof(int), 0, SIZE - 1, partition);
    end1 = clock();
    time_use1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
    printf("\nTime for quick_sort: %f ", time_use1);
    // for (int i = 0; i < SIZE; i++)
    // {
    //     printf("%3d", a[i]);
    // }
    printf("\n");
    return 0;
}