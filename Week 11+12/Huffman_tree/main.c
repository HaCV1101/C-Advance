#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "huffman.h"

double oo = 1e10;

const int ArraySize = 300;

char HuffmanArray[400][10];

char HuffmanTable[400][40];

int CodePos[200];

void printNode(Node* root, int stt)
{
    if(root == NULL) return;
    root->pos = stt;
    //printf("node: %3s %3d - pos%3d\n", root->key, root->val, root->pos);
    strcpy(HuffmanArray[stt], root->key);
    if(strcmp(root->key,"-1") != 0) CodePos[(root->key)[0]] = stt;

    Node* left = root->left;
    Node* right = root->right;
    // if(left != NULL)
    //     printf("   - left: %3s %3d\n", left->key, left->val);
    // if(right != NULL) 
    //     printf("   - right: %3s %3d\n", right->key, right->val);


    printNode(left, 2 * stt + 1);
    printNode(right, 2 * stt + 2);
    
}


void getTable(Node* root)
{
    if(root == NULL) return;
    //if(strcmp(root->key, "-1") != 0)
    int pos = root->pos;
    if(pos != 0)  {
        char now[30];
        char new[30];
        strcpy(now, HuffmanTable[(pos - 1) / 2]);
        if(strcmp(now, "-1") == 0){
            if(pos % 2 != 0) strcpy(new,"0");
            else strcpy(new, "1");
            strcpy(HuffmanTable[pos], new);
        }
        else {
            strcpy(new, now);
            if(pos % 2 != 0) strcat(new,"0");
            else strcat(new, "1");
            strcpy(HuffmanTable[pos], new);
        }
    }
    Node* left = root->left;
    Node* right = root->right;
    if(left != NULL)
        getTable(left);
    if(right != NULL)
        getTable(right);
}






void input(HuffmanTree *H, FILE* inp, char* InPut)
{
    //FILE* inp = fopen(filename, "r");
    if(inp == NULL)
    {
        printf("Can't open file\n");
        return;
    }
    //int count[500];
    char tmp;
    int i = 0;
    while (1) {
        tmp = getc(inp);
        if(tmp == EOF) break;
        //printf("%4c %4d\n", tmp, tmp);
        count(H, tmp);
        InPut[i] = tmp;
        i++;
    }
    process(H);
    printNode(H->root, 0);
    strcpy(HuffmanTable[0], "-1");
    getTable(H->root);
    //fclose(inp);
}


void Decompress(char* now, int index, Node* root, char* result, HuffmanTree* H)
{
    //printf("%s\n", result);
    if(index > strlen(now)) return;
    if(strcmp(root->key,"-1") != 0) {
        //printf("%d, " ,index);
        strcat(result, root->key);
        Decompress(now, index , H->root, result, H);
        return;
    }
    else {
        if(now[index] == '0') Decompress(now, index + 1, root->left, result, H);
        else Decompress(now, index + 1, root->right, result, H);
    }
}


void compressFile(FILE* in, FILE* out, HuffmanTree* H)
{
    for(int i = 0; i < ArraySize; i++)   strcpy(HuffmanArray[i], "000");
    char compressCode[5000];
    strcpy(compressCode,"");
    char inPut[2000];
    strcpy(inPut, "");
    input(H, in, inPut);
    for(int i = 0; i < ArraySize; i++)  {
        if(strcmp(HuffmanArray[i], "000") != 0 && strcmp(HuffmanArray[i], "-1") != 0) {
            printf("%4d %3s %10s\n",i ,HuffmanArray[i], HuffmanTable[i]);
            H->height = log2(i) + 1;
        }
    }
    printf("height: %d\n", H->height);
    for(int i = 0; i < 200; i++) {
        if(CodePos[i] != 0) 
            printf("%c num %d -> pos: %d\n",i, i,CodePos[i]);
    }
    printf("%s\n", inPut);
    int MaxSize = pow(2,H->height);
    fprintf(out,"HM | ");
    for(int i = 0; i < MaxSize; i++) {
        if(strcmp(HuffmanArray[i], "000") != 0 ) {
            if(strcmp(HuffmanArray[i], "-1") != 0 )
                fprintf(out, "%s", HuffmanArray[i]);
            else fprintf(out, "*");
        }
        else fprintf(out, " ");
        if(i < MaxSize - 1) fprintf(out,",");
    }
    fprintf(out,"| %d | ",MaxSize - 1);
    for(int i = 0; i < strlen(inPut); i++) {
        int pos = CodePos[inPut[i]];
        strcat(compressCode,HuffmanTable[pos]);
        fprintf(out,"%s ",HuffmanTable[pos]);
    }
    printf("%s\n", compressCode);
    
    char result[200];
    strcpy(result, "");
    Decompress(compressCode, 0, H->root, result, H);
    printf("%s\n", result);
    // char now[30];
    // strcpy(now, "");
    // strcpy(HuffmanTable[0], "-1");
    // getTable(H->root);



}



int main()
{
    HuffmanTree *H = create();
    FILE* in = fopen("inp.txt", "r");
    FILE* out = fopen("out.txt", "w");
    compressFile(in, out, H);
    fclose(in);
    fclose(out);
    
}
