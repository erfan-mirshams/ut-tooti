#ifndef INOUT_H_
#define INOUT_H_
#include <stdio.h>
#define read_line() read_line_from_file(stdin);

char *read_line_from_file(FILE *input);
char **split_words(char *input);
int words_size(char **words);
#endif //INOUT_H_
