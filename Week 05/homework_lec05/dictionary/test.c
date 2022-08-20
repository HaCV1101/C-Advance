#include<stdio.h>
#include<stdlib.h>

int main()
{
    char tmp[50];
    while(fgets(tmp, 50, stdin) != NULL)
    {
        //getc(stdin);
        printf("%s", tmp);
    }
}