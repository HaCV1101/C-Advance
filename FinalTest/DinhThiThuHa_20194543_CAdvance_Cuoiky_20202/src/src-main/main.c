#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int menuVaLuaChon(int a, int b)
{
    int luaChon, buff;
    char c;
    printf("\n\t\t\t|============================================|\n");
    printf("\t\t\t|=======           BK-CIRCLE         ======|\n");
    printf("\t\t\t|============================================|\n");
    printf("\t\t\t|1.%-42s|\n", "Input data");
    printf("\t\t\t|2.%-42s|\n", "List friend ");
    printf("\t\t\t|3.%-42s|\n", "Popular person");
    printf("\t\t\t|4.%-42s|\n", "Check friend");
    printf("\t\t\t|5.%-42s|\n", "Suggest friend");
    printf("\t\t\t|6.%-42s|\n", "Exit");
    printf("\t\t\t|============================================|\n");
    do
    {
        __fpurge(stdin);
        printf("Nhap vao lua chon cua ban:");
        buff = scanf("%d%c", &luaChon, &c);
        if (buff != 2 && c != '\n' || luaChon < a || luaChon > b)
            printf("Ban da nhap sai cu phap\n");
    } while (buff != 2 && c != '\n' || luaChon < a || luaChon > b);
    return luaChon;
}

int getId(Graph g, char *name)
{
    JRB ptr;
    jrb_traverse(ptr, g.vertices)
    {
        if (strcmp(jval_s(ptr->val), name) == 0)
            return jval_i(ptr->key);
    }
    return -1;
}

void inDegJrb(Graph g, JRB g1)
{
    int out[1000];
    int value;
    JRB node, tree = g.vertices;
    jrb_traverse(node, tree)
    {
        int key = jval_i(node->key);
       
        value = indegree(g, key, out);
        jrb_insert_int(g1, key, new_jval_i(value));
        
    }
}

int main()
{
    int n, id, so, index1 = 0, v_num, v1_num, out[20], arr[20];
    int id1;
    int nline;
    char name[256], str1[256], *cut;
    char ten[100], buff, c;
    Graph g = createGraph();
    JRB ptr, ptr1;
    FILE *fpt = fopen("users.txt", "r+");
    FILE *fpt1 = fopen("friends.txt", "r+");
    int thoat = 0, luaChon = 0, dieukien = 0, index = 0;
    char **A = (char **)malloc(100 * sizeof(char)), *token = (char *)malloc(100 * sizeof(char));

    char str[256], ch, ch1;
    do
    {
        luaChon = menuVaLuaChon(1, 6);
        switch (luaChon)
        {
        case 1:

            puts("Noi dung file user.txt:");
            fscanf(fpt, "%d\n", &nline);
            printf("%d\n", nline);
            for (int i = 0; i < nline; i++)
            {
                fscanf(fpt, "%d %s\n", &id, name);
                printf("%d %s\n", id, name);
                addVertex(g, id, strdup(name));
            }
            puts("Noi dung file friends.txt:");
            while (!feof(fpt1) && fgets(str, 256, fpt1))
            {
                printf("%s", str);
                cut = strtok(str, " ");
                strcpy(name, cut);
                while (1)
                {
                    cut = strtok(NULL, " \n");
                    if (!cut)
                        break;
                    addEdge(g, atoi(name), atoi(cut), 1);
                    addEdge(g, atoi(cut), atoi(name), 1);
                }
            }
            puts(" ");
            break;
        case 2:
            printf("Nhap ten:");
            fgets(str, 256, stdin);
            str[strlen(str) - 1] = 0;
            id = getId(g, str);
            if (id == -1)
                printf("khong ton tai");
            else
            {
                n = outdegree(g, id, out);
                if (n == 0)
                    printf("khong co ban");
                for (int i = 0; i < n; i++)
                {
                    printf("%s\n", getVertex(g, out[i]));
                }
            }
            break;
        case 3:
            inDegJrb(g, ptr);
            // jrb_rtraverse(ptr1, ptr)
            // {
            //     printf("%s:%d", getVertex(g,jval_i(ptr1->key)), jval_i(ptr1->val));
            // }

            break;
        case 4:
            printf("Nhap ten 1:");
            fgets(str, 256, stdin);
            str[strlen(str) - 1] = 0;
            id = getId(g, str);
            if (id == -1)
                printf("khong ton tai");

            printf("Nhap ten 2:");
            fgets(str1, 256, stdin);
            str1[strlen(str1) - 1] = 0;
            id1 = getId(g, str1);
            if (id1 == -1)
                printf("khong ton tai");

            n = outdegree(g, id, out);
            for (int i = 0; i < n; i++)
            {
                if (out[i] == id1)
                {
                    printf("La ban cua nhau");
                    index1 = 1;
                }
            }
            if (index1 != 1)
                printf("Khong la ban cua nhau");
            break;
        case 5:

            break;
        case 6:

            printf("\t\t\t\t |=========================|\n");
            printf("\t\t\t\t ||-KET THUC CHUONG TRINH-||\n");
            printf("\t\t\t\t |=========================|\n");
            thoat = 1;
            break;
        }
    } while (thoat != 1);
    fclose(fpt);
    return 0;
}