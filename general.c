#include "general.h"

/* fills string a with b */
int string_fill(char *a, char *b){
    int sz = strlen(b) + 1;
    a = (char *)malloc(sizeof(char) * sz);
    if(a == NULL){
        return FALSE;
    }
    int i;
    for(i = 0; i < sz; i++){
        a[i] = b[i];
    }
    return TRUE;
}
