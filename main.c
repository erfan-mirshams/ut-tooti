#include "general.h"
#include "in-out.h"
#include "struct.h"

int main(){
    char *ch = read_line();
    char **words = split_words(ch), **ptr;
    for(ptr = words; *ptr != NULL; ptr++){
        printf("%s\n", *ptr);
    }
    free(words);
    free(ch);
}
