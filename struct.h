#ifndef STRUCT_H_
#define STRUCT_H_
typedef struct user user;
typedef struct post post;
typedef struct like like;

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
#endif //STRUCT_H_
