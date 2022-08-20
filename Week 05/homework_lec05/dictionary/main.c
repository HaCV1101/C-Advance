#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include "dic.h"
//#include"graphics.h"



typedef long long ll;

// int tty_break()
// {
// 	initscr();
// 	cbreak();
// 	return 0;
// }

// int tty_getchar()
// {
// 	return getch();
// }

// int tty_fix()
// {
// 	endwin();
// 	return 0;
// }

// ll change(char* X)
// {
//     int n = strlen(X);
//     ll res = 0;
//     for(int i = 0; i < n; i++)
//         res = res * 10 + (X[i] - '0');
//     return res;
// }

void input(Dic* D, char* filename)
{
    FILE* inp = fopen(filename, "r");
    char tmp[50];
    char key[30], val[30];
    while (fgets(tmp, 50, inp) != NULL)
    {
        tmp[strlen(tmp) - 1] = '\0';
        int n = strlen(tmp);
        int i = 0, j;
        key[0] = '\0';   val[0] = '\0';
        while(tmp[i] == ' ') i++;     j = i;
        while(tmp[j] != ' ')
        {
            key[j - i] = tmp[j];
            j++; 
        }key[j - i] = '\0';
        i  = j;
        while(tmp[i] == ' ') i++;     j = i;
        while(j < n)
        {
            val[j - i] = tmp[j];
            j++; 
        }val[j - i] = '\0';
        printf("%s  ", key);
        printf("%s\n", val);
        add(D, key, val);
    }
    fclose(inp);
}


int main()
{
    Dic* D = initial("run1_db");
    //Dic* D2 = initial("run2_db");
    printf("Input data's filenames(-1 for end): ");
    char filename[30];
    while(1)
    {
        fscanf(stdin,"%s", filename);
        if(strcmp(filename, "-1") == 0) break;
        input(D, filename);
        printf("%s\n", filename);
    }
    getchar();
    Print(D);
    char c;
    char tmp[30];
    int i = 0, j = 0;
    list* L;
    Dic* X;
    int d = 0;
    while(1)
    {
        //c = getch();
        c = getc(stdin);
        //if(c == '\t') printf("\r");
        printf("%c  ", c);
        if(c == '0') break;
        if(c == '\n') 
        {
            tmp[i] = '\0';
            printf("%s\n", Search(D, tmp) );
            tmp[0] ='\0'; i = 0;
            j = 0;
            free(L);
            d = 0;
            continue;
        }
        if(c == '\t')
        {
            printf("dd\n");
            if(d == 0)
            {
                int *Maxx;
                X = FindSub(D, tmp, Maxx);
                printf("ff");
                L = run(X, *Maxx);
                strcpy(tmp, (L + j) -> A);
                d = 1;
                printf("\r%s", tmp);
            }
            else 
            {
                j++;
                strcpy(tmp, (L + j) -> A);
                printf("\r%s", tmp);
            }
        }
        tmp[i] = c;
        i++;
    }   
    btcls(D);
}