#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

JRB dns;
int Number;

void do_print();
void do_add(char *dn, char *ip);
void do_remove(char *dn);
void do_lookup_ip(char *dn);
void do_lookup_dn(char *ip);

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Usage: prog print \n       prog add [dn] [ip] \n       prog remove [dn]\n       prog ip [dn]\n       prog dn [ip]\n");
        return 0;
    }

    if (strcmp(argv[1], "print") == 0)
    {
        if (argc != 2)
        {
            printf("Invalid parameters\n");
            return 0;
        }
        do_print();
        return 0;
    }
    if (strcmp(argv[1], "add") == 0)
    {
        if (argc != 4)
        {
            printf("Invalid parameters\n");
            return 0;
        }
        do_add(argv[2], argv[3]);
        return 0;
    }
    if (strcmp(argv[1], "remove") == 0)
    {
        if (argc != 3)
        {
            printf("Invalid parameters\n");
            return 0;
        }
        do_remove(argv[2]);
        return 0;
    }
    if (strcmp(argv[1], "ip") == 0)
    {
        if (argc != 3)
        {
            printf("Invalid parameters\n");
            return 0;
        }
        do_lookup_ip(argv[2]);
        return 0;
    }
    if (strcmp(argv[1], "dn") == 0)
    {
        if (argc != 3)
        {
            printf("Invalid parameters\n");
            return 0;
        }
        do_lookup_dn(argv[2]);
        return 0;
    }
    printf("Invalid parameters\n");
    return 0;
}    ///////////////////////////////////////////////////////////////


void PrintFile()
{
    FILE *out = fopen("dns.txt", "w");
    if(out == NULL) {
        printf("error\n");
        return;
    }
    fprintf(out, "%d\n", Number);
    JRB node;
    jrb_traverse(node, dns)
    {
        char Dns[250], ip[250];
        strcpy(Dns, jval_s(node->key));
        strcpy(ip, jval_s(node->val));
        fprintf(out,"%s\n%s\n", Dns, ip);
    }
    fclose(out);
}

void print_entry(char *dn, char *ip)      /////// in ra tên miền và ip
{
    printf("%s => %s\n", dn, ip);
}

void Travel() ////// duyet toan bo JRB và in ra
{
    JRB node;
    jrb_traverse(node, dns)
    {
        char Dns[250], ip[250];
        strcpy(Dns, jval_s(node->key));
        strcpy(ip, jval_s(node->val));
        print_entry(Dns, ip);
    }
}

int getInt(char *tmp)       ////// doi tmp -> int
{
    int res = 0;
    for (int i = 0; i < strlen(tmp); i++)
    {
        if (tmp[i] >= '0' && tmp[i] <= '9')
            res = res * 10 + tmp[i] - '0';
    }
    return res;
}


int Input()
{
    FILE *inp = fopen("dns.txt", "r");
    if (inp == NULL) /////// file không tồn tại
    {
        printf("error\n");
        return;
    }
    dns = make_jrb();
    char tmp[250];
    int count, i = 0, num = 0;
    char dn[1050][250], ip[1050][250];
    int check = 1;
    while (fgets(tmp, 250, inp) != NULL)
    {
        if (tmp[strlen(tmp) - 1] == '\n')     tmp[strlen(tmp) - 1] = '\0';
        //printf("%s\n", tmp);
        i++;
        if (i == 1){
            count = getInt(tmp);
            if(count == 0)     /////  dòng đầu k phải số
            {
                check = 0;
                break;
            }
        }
        else
        {
            if (i % 2 == 0)/////// tên miền
            { 
                num++;
                strcpy(dn[num], tmp);
            }
            else   //////// địa chỉ ip
            {
                if(tmp[0] < '0' || tmp[0] > '9') {
                    check = 0;
                    break;
                }
                strcpy(ip[num], tmp);
            }
        }
    }
    if (i != count * 2 + 1) //////// sai cấu trúc
        check = 0;
    if (check == 0)
    {
        printf("error\n");
        return check;
    }
    Number = num;
    for (int i = 1; i <= Number; i++)
        jrb_insert_str(dns, strdup(dn[i]), new_jval_s(strdup(ip[i])));
    fclose(inp);
    return check;
}

void do_print() ///// đọc và hiển thị thông tin miền
{
    Input();
    Travel();
}

void do_add(char *dn, char *ip) //// thêm tên miền và địa chỉ ip
{
    int check = Input();
    if(check == 0) return;
    JRB node = jrb_find_str(dns, dn);
    if (node == NULL)
    {
        jrb_insert_str(dns, strdup(dn), new_jval_s(strdup(ip)));
        Number++;
    }
    else
    {
        jrb_delete_node(node);
        jrb_insert_str(dns, strdup(dn), new_jval_s(strdup(ip)));
    }
    Travel();
    PrintFile();
}

void do_remove(char *dn)    //// xóa tên miền
{
    int check = Input();
    if(check == 0) return;
    JRB node = jrb_find_str(dns, dn);
    if(node != NULL) 
    {
        jrb_delete_node(node);
        Number--;
    }
    Travel();
    PrintFile();
}

void do_lookup_ip(char *dn)      /// tìm địa chỉ ip qua tên miền
{
    int check = Input();
    if(check == 0) return;
    JRB node;
    node = jrb_find_str(dns,dn);
    if(node == NULL) printf("not found\n");
    else
        print_entry(jval_s(node->key), jval_s(node->val));
}

void do_lookup_dn(char *ip)      /// tìm tên miền theo địa chỉ ip
{
    int check = Input();
    if(check == 0) return;
    int dd = 0;
    JRB node;
    jrb_traverse(node,dns)
    {
        char Dns[250], IP[250];
        strcpy(Dns, jval_s(node->key));
        strcpy(IP, jval_s(node->val));
        if(strcmp(IP, ip) == 0)
        {   
            print_entry(Dns, IP);
            dd= 1;
        }
    }
    if(dd == 0) printf("not found\n");
}