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
};

struct post {
    int id;
    int user_id;
    int like_cnt;
    char *content;
    post *next;
};

struct like {
    int id;
    int user_id;
    int post_id;
    like *next;
};
#endif //STRUCT_H_
