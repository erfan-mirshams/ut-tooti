#include "general.h"
#include "in-out.h"

/* reads a single line of string from input. suits to different end of line conventions in different OSes */
char *read_line_from_file(FILE *input){
    int line_length = 0;
    char *line = (char *)malloc(sizeof(char));
    CHECK_MAL(line);
    *(line) = '\0';

    char temp_char = '\0';
    /* reads the next character */
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
          /* for Mac and Windows systems */
          temp_char = getc(input);
          if(temp_char != '\n'){
            ungetc(temp_char, input);
          }
          return line;
          break;
        default:
          line_length++;
          line = (char *)realloc(line, sizeof(char) * (line_length + 1));
          CHECK_MAL(line);
          line[line_length] = '\0';
          line[line_length - 1] = temp_char;
          break;
        }
    }
    return line;
}

/* splits a line input into words. seperates words by whitespace if the first word is post won't split next words */
char **split_words(char *input){
    char **res = (char **)malloc(sizeof(char*));
    CHECK_MAL(res);
    *res = NULL;
    int i;
    for(i = 0; ; i++){
        /* remove whitespace before word */
        while (isspace(*(input))) {
            input++;
        }
        char *cur = input;
        int post_flag = (i == 1 ? !strcmp(*res, "post") : FALSE);
        /* read graphical characters with the exception of when the first word is post */
        while (isgraph(*(input)) || (post_flag && *input != '\0')) {
            input++;
        }
        /*trim whitespace from end of the line*/
        if(cur == input){
            break;
        }
        /* add to the pile of words */
        res = (char **)realloc(res, sizeof(char *) * (i + 2));
        CHECK_MAL(res);
        res[i + 1] = NULL;
        res[i] = cur;
        if(*input == '\0'){
            break;
        }
        *(input++) = '\0';
    }
    return res;
}

/* returns size of char** */
int words_size(char **words) {
  int i;
  for (i = 0; *(words++) != NULL; i++)
    ;
  return i;
}
