#include "general.h"

/* fills string a with b */
char *string_fill(char *b){
    char *a;
    int sz = strlen(b) + 1;
    a = (char *)malloc(sizeof(char) * sz);
    if(a == NULL){
        return NULL;
    }
    int i;
    for(i = 0; i < sz; i++){
        a[i] = b[i];
    }
    return a;
}
