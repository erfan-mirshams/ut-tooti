#ifndef INOUT_H_
#define INOUT_H_
#include <stdio.h>
#define read_line() read_line_from_file(stdin);
#define MAXN 300

char *read_line_from_file(FILE *input);
char **split_words(char *input);
#endif //INOUT_H_
