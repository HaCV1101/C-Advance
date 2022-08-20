#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"PB.h"

BTint change(char* X)
{
    int n = strlen(X);
    BTint res = 0;
    for(int i = 0; i < n; i++)
    {
        res = res * 10 + (X[i] - '0');
    }
    return res;
}

void inputFile(PB* P, char* filename)
{
    FILE* inp = fopen(filename, "r");
    // char tmp[50];
    // char key[30], value[30];
    // BTint val;
    // while(fgets(tmp, 50, inp) != NULL)
    // {
    //     int i = 0, j;
    //     tmp[strlen(tmp) - 1] = '\0';
    //     //printf("%s\n", tmp);
    //     key[0] = '\0';
    //     value[0] = '\0';
    //     while(tmp[i] == ' ') i++;
    //     j = i;
    //     while(tmp[j] != ' ')
    //     {
    //         key[j-i] = tmp[j];
    //         j++;
    //     }
    //     i = j;
    //     while(tmp[i] == ' ') i++;
    //     j = i;
    //     while(tmp[j] != ' ')
    //     {
    //         value[j-i] = tmp[j];
    //         j++;
    //     }
    //     val = change(value);
    //     printf("%s %d\n", key, val);
    //     addNode(P, key, val);
    // }
    int n;
    fscanf(inp,"%d", &n);
    printf("%d\n", n);
    char key[30];
    BTint val;
    for(int i = 1;i <= n; i++)
    {
        fscanf(inp, "%s %d", key, &val);
        //key[strlen(key)] = '\0';
        //printf("%s %d\n",  key, val);
        //printf("%ld\n", strlen(key));
        addNode(P, key, val);
        //printf("%d\n", search(P->tree, key) );
    }
    fclose(inp);
}

void printTree(PB* P)
{
    char key[ZKYLEN+1];
    BTint i;
    //printf("đ\n");
    if (P != NULL) {
        //b2 = btcrt("run",0,FALSE);
        //if (b2 != NULL) {
            //puts("..copying");
            btpos(P,ZSTART);
            while (bnxtky(P,key,&i) == 0) {//binsky(b2,key,i);
                printf("%s aa\n", key);
                //printf("1");
            }
            //btcls(b2);
        }
        //btcls(b1);
    //}
    //printf("%ld\n", strlen("Amber"));
    printf("%d\n",search(P, "Amber") );
}

void deleteFile(PB* P)
{
    FILE* del = fopen("del.txt", "r");
    char tmp[30];
    while (fscanf(del, "%s", tmp) != EOF)
    {
        //tmp[strlen(tmp)] = '\0';
        // int n = strlen(tmp);
        // tmp[n-1] = '\0';
        printf("%s\n", tmp);
        Delete(P, tmp);
    }
    fclose(del);
}

int main()
{
    PB* P = initial();
    char filename[30];
    FILE* inp = fopen("test.inp","r");
    while(1)
    {
        fscanf(inp,"%s", filename);
        if(strcmp(filename, "-1") == 0) break;
        inputFile(P,filename);
        //printf("\n%d\n",search(P->tree, "Amber\0") );
    }
    fclose(inp);
    printTree(P);
    printf("%d\n",search(P, "Amber") );
    deleteFile(P);
    printf("â\n");
    printTree(P);
    btcls(P);
}
