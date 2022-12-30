#include "general.h"
#include "in-out.h"
#include <ctype.h>
#include <stdlib.h>

char *read_line_from_file(FILE *input){
    int line_length = 0;
    char *line = (char *)malloc(sizeof(char));
    *(line) = '\0';

    char temp_char = '\0';
    while (TRUE) {
        if(line_length == MAXN){
            return NULL;
        }
        temp_char = getc(input);
        switch (temp_char) {
        case '\n':
          return line;
          break;
        case EOF:
          return line;
          break;
        case '\r':
          break;
        default:
          line_length++;
          line = (char *)realloc(line, sizeof(char) * (line_length + 1));
          line[line_length] = '\0';
          line[line_length - 1] = temp_char;
          break;
        }
    }
    return line;
}

/*splits a line input into words. seperates words by whitespace*/
char **split_words(char *input){
    char **res = (char **)malloc(sizeof(char*));
    int i;
    for(i = 0; ; i++){
        res = (char **)realloc(res, sizeof(char *) * (i + 2));
        res[i + 1] = NULL;
        while (isspace(*(input))) {
            input++;
        }
        char *cur = input;
        while (isalnum(*(input))) {
            input++;
        }
        res[i] = cur;
        if(*input == '\0'){
            break;
        }
        *(input++) = '\0';
    }
    return res;
}
