#ifndef GENERAL_H_
#define GENERAL_H_
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define COMMAND_CNT 9
#define CHECK_MAL(ptr) if((ptr) == NULL)mal_fail()
char *string_fill(char *b);
void mal_fail();
#endif //GENERAL_H_
