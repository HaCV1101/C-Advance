#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio_ext.h>
#include <string.h>
#define SMALL_SIZE 9
#define HUGE_SIZE 100000

typedef union
{
    int i;
    long l;
    float f;
    double d;
    char c;
    void *v;
    char *s;

} Jval;

Jval new_jval_i(int i)
{
    Jval j;
    j.i = i;
    return j;
}
Jval new_jval_l(long l)
{
    Jval j;
    j.l = l;
    return j;
}
Jval new_jval_f(float f)
{
    Jval j;
    j.f = f;
    return j;
}
Jval new_jval_d(double d)
{
    Jval j;
    j.d = d;
    return j;
}
Jval new_jval_c(char c)
{
    Jval j;
    j.c = c;
    return j;
}
Jval new_jval_v(void *v)
{
    Jval j;
    j.v = v;
    return j;
}
Jval new_jval_s(char *s)
{
    Jval j;
    j.s = s;
    return j;
}
int jval_i(Jval j)
{
    return j.i;
}
long jval_l(Jval j)
{
    return j.l;
}
char *jval_s(Jval j)
{
    return j.s;
}
char jval_c(Jval j)
{
    return j.c;
}
float jval_f(Jval j)
{
    return j.f;
}
double jval_d(Jval j)
{
    return j.d;
}
void *jval_v(Jval j)
{
    return j.v;
}

Jval *creatArray(int size)
{
    Jval *a;
    a = (Jval *)malloc(size * sizeof(Jval));
    srand((int)time(NULL));
    for (int i = 0; i < size; i++)
    {
        *(a + i) = new_jval_i(rand() % SMALL_SIZE);
    }
    return a;
}

int compare_i(Jval *a, Jval *b)
{
    if (jval_i(*a) == jval_i(*b))
        return 0;
    else if (jval_i(*a) < jval_i(*b))
        return -1;
    else
        return 1;
}

void SWAP(Jval *a, Jval *b)
{
    Jval *temp;
    temp = (Jval *)malloc(sizeof(Jval));
    *temp = *a;
    *a = *b;
    *b = *temp;
    free(temp);
}

int search_gen(Jval buf[], int l, int r, Jval item, int (*compare)(Jval *x, Jval *y))
{

    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare(&item, &(buf[i]));
    if (res == 0)
        return i;
    else if (res < 0)
        return search_gen(buf, l, i - 1, item, compare);
    else
        return search_gen(buf, i + 1, r, item, compare);
}

void sort_gen(Jval a[], int l, int r, int (*compare)(Jval *x, Jval *y))
{
    if (r < l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (compare(&a[++i], &a[r]) < 0)
            ;
        while (compare(&a[r], &a[--j]) < 0)
        {
            if (j == l)
                break;
        }
        if (i >= j)
            break;
        SWAP(&a[i], &a[j]);
        if (compare(&a[i], &a[r]) == 0)
            SWAP(&a[++p], &a[i]);
        if (compare(&a[j], &a[r]) == 0)
            SWAP(&a[--q], &a[j]);
    }
    SWAP(&a[i], &a[r]);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        SWAP(&a[k], &a[j--]);
    for (int k = r - 1; k >= q; k--)
        SWAP(&a[k], &a[i++]);
    sort_gen(a, l, j, compare);
    sort_gen(a, i, r, compare);
}

int main()
{
    Jval *a;
    int res;
    Jval item;
    item.i = 5;
    a = creatArray(SMALL_SIZE);
    for (int i = 0; i < SMALL_SIZE; i++)
    {
        printf("%d ", jval_i(a[i]));
    }
    printf("\n");
    //sapxep
    sort_gen(a, 0, SMALL_SIZE - 1, compare_i);
    for (int i = 0; i < SMALL_SIZE; i++)
    {
        printf("%d ", jval_i(a[i]));
    }
    printf("\n");
    //timkiem
    res = search_gen(a, 0, SMALL_SIZE - 1, item, compare_i);
    printf("%d", res);

    printf("\n");

    return 0;
}