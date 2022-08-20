#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

char* name[300];
long number[300];

int main()
{
    JRB b;
    JRB bn;
    FILE* inp = fopen("a.inp","r");
    //IS is;
    int MAXX = 30;
    int n;
    fscanf(inp,"%d",&n);
    getc(inp);
    printf("%d\n", n);
    b = make_jrb();
    for(int i=1;i<=n;i++)
    {
        //char *c;
        //fgets(name+i, MAXX, inp);
        fscanf(inp, "%s %ld", name + i, &number[i]);
        //printf("%s %ld\n", name+i, number[i]);
        JRB a = jrb_find_str(b,name+i);
        // printf("%ld", jval_l(a->val));
        if(a != NULL) 
        {
            a->val = new_jval_l(number[i]);
            continue;
        }
        // printf("  %d\n", i);
        (void) jrb_insert_str(b, strdup(name+i), new_jval_v(number[i]));
    }
    fclose(inp);
    //is = new_inputstruct("a.inp");
    

    // while (get_line(is) >= 0) {
    //     (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(number));
    // }

    int i = 0;
    jrb_traverse(bn, b) {
        i++;
        printf("%5d %8s %9ld \n",i, jval_s(bn->key), jval_l(bn->val));
    }
}