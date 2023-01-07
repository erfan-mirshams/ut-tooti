#ifndef GENERAL_H_
#define GENERAL_H_
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define COMMAND_CNT 10
#define MAXN 300
#define MAX(a, b) ((a) > (b) ? a : b)
#define CHECK_MAL(ptr) if((ptr) == NULL)mal_fail()
char *string_fill(char *b);
int is_pos_int(char *ch);
void mal_fail();
#endif //GENERAL_H_
