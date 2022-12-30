#include "general.h"
#include "in-out.h"
#include "struct.h"

int main(){
    char *ch = read_line();
    char **ptr = split_words(ch);
    for(; *ptr != NULL; ptr++){
        printf("%s\n", *ptr);
    }
}
