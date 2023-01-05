#include "general.h"
#include <stdio.h>

/* fills string a with b */
char *string_fill(char *b){
    char *a;
    int sz = strlen(b) + 1;
    a = (char *)malloc(sizeof(char) * sz);
    CHECK_MAL(a);
    int i;
    for(i = 0; i < sz; i++){
        a[i] = b[i];
    }
    return a;
}

/* checks whether ch can be cast to an integer */
int is_pos_int(char *ch){
    char c;
    while((c = *(ch++))){
        if(!isdigit(c)){
            return FALSE;
        }
    }
    return TRUE;
}

/* abort when malloc fails */
void mal_fail(){
    printf("error: Memory Allocation Failed!\n");
    exit(EXIT_FAILURE);
}
