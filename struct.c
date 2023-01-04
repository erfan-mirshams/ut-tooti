#include "struct.h"

struct user {
    int id;
    char *name;
    char *pass;
    int post_cnt;
    user *next;
    user *prev;
};

struct post {
    int id;
    int user_id;
    int like_cnt;
    char *content;
    post *next;
    post *prev;
};

struct like {
    int user_id;
    int post_id;
    like *next;
    like *prev;
};
