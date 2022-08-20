#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

// int change(char* x)
// {
//     int n = strlen(x);
//     int res = 0;
//     for(int i = 0; i < n; i++)
//     {
//         res = res * 10 + (x[i] - '0');
//     }
//     return res;
// }

void input(BTA* btfile)
{
    FILE* inp = fopen("inp.txt", "r");
    int n;
    fscanf(inp, "%d", &n);
    for(int i=1;i<=n;i++)
    {
        char key[20];
        BTint val;
        fscanf(inp,"%s %d", key, &val);
        printf("%s %d\n",key, val);
        binsky(btfile, key, val);
    }
    fclose(inp);
}

int main(int argc, char *argv[])
{
    BTA *btfile;
    btinit();
    btfile = btcrt("test_db",0,FALSE);
    // char filename[30];
    // scanf("%s", filename);
    input(btfile);

    BTint* a;
    bfndky(btfile,"a", a);
    if(a != NULL)  printf("%d\n", *a);

    btcls(btfile);
    return 0;
}