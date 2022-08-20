#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#include "bt-5.0.1/inc/btree.h"

#define WORD_LENGHT 255
#define MEANING_LENGHT 10000

void separate_mean(char mean[MEANING_LENGHT]);
int convert_text_to_bt(char *file);
int file_exists(char *pathname);
int main()
{
    BTA *data;
    btinit();
    //Khoi tao lam dau
    if (!file_exists("resource.dat")) {       
        convert_text_to_bt("anhviet.txt");
    }
    data = btopn("resource.dat", 0, 0);

    int scan, chon1, chon2;

    char anh[WORD_LENGHT];
    char viet[MEANING_LENGHT];
    char suggest_word[WORD_LENGHT];	

    int size, value;
    printf("Nhap tu tieng anh: ");
    __fpurge(stdin);
    fgets(anh,WORD_LENGHT,stdin);
    anh[strlen(anh)-1] = 0;
    if (bfndky(data, anh, &size) == 0)
    {
            //strcpy(suggest_word, word);
            bnxtky(data,suggest_word,&value);
            printf("%s\n",suggest_word);

    }else{
        printf("Khong tim thay.\n");
    }
    btcls(data);
    return 0;    
}

void separate_mean(char mean[MEANING_LENGHT])
{
    int m = 0;
    int n = 1;
    while (mean[n] != '\0')
    {
        if (mean[n] == '\\' && mean[n + 1] == 'n')
        {
            mean[m++] = '\n';
            n += 2;
        }
        else
        {
            if (m != n)
                mean[m++] = mean[n++];
            else
            {
                n++;
                m++;
            }
        }
    }
    mean[m] = '\0';
}

int convert_text_to_bt(char *file)
{
    FILE *data;
    if ((data = fopen(file, "r")) == NULL)
    {
        printf("Khong mo duoc file\n");
        return 0;
    }

    BTA *convert;
    convert = btcrt("resource.dat", 0, 0);  //?

    char word[WORD_LENGHT], mean[MEANING_LENGHT];
    int line;   //?

    while (fscanf(data, "%[^\t]", word) == 1)
    {
        fgets(mean, MEANING_LENGHT, data);
        line++;
        separate_mean(mean);
        btins(convert, word, mean, strlen(mean) + 1);
    }
    
    printf("%d lines.\n", line);
    btcls(convert);
    fclose(data);
    return 1;
}

int file_exists(char *pathname)
{
    FILE* f;

    f = fopen(pathname,"r");
    if (f == NULL) {
        return FALSE;
    }
    else {
        fclose(f);
    }
    return TRUE;
}
