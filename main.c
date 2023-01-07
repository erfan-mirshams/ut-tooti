#include "general.h"
#include "in-out.h"
#include "struct.h"
#include "user.h"
#include "post.h"
#include "like.h"
#include <stdio.h>

/* static variables */
static user *user_head, *cur_user;
static int user_id_cnt, post_id_cnt, like_id_cnt;
static post *post_head;
static like *like_head;

/* reads a line into ch and splits the words into words */
void read_command(char **ch, char ***words){
    *ch = read_line();
    *words = split_words(*ch);
}

/* prints the posts in a desirable format */
void write_posts(post **posts){
    for(; *posts != NULL; posts++){
        printf("\n");
        printf("Id: %d\n", (*posts) -> id);
        printf("Content:\n%s\n", (*posts) -> content);
        printf("Like Count: %d\n", (*posts) -> like_cnt);
    }
}

/* processes the command */
int process(char **words, int sz){
    char *command_names[] = {"signup", "login", "logout", "find_user", "post", "delete", "info", "like", "exit", "unlike"};
    int command_input_size[] = {3, 3, 1, 2, 2, 2, 1, 3, 1, 3};
    int command_id = -1, i;
    for(i = 0; i < COMMAND_CNT; i++){
        /* if the command is valid */
        if(!strcmp(*words, command_names[i]) && sz == command_input_size[i]){
            command_id = i;
            continue;
        }
    }

    /* temporary variables */
    user *temp_usr;
    int x_id;
    int y_id;
    post **temp_posts;
    switch (command_id) {
        case 0:
            /* repeated username */
            if(!signup(user_head, &user_id_cnt, words[1], words[2])){
                printf("error: This username is taken!\n");
                return TRUE;
            }
            cur_user = login(user_head, words[1], words[2]);
            printf("Signup successful. User %s created.\n", cur_user -> name);
            break;
        case 1:
            temp_usr = login(user_head, words[1], words[2]);
            /* wrong username or password */
            if(temp_usr == NULL){
                printf("error: unsuccessful login!\n");
                return TRUE;
            }
            cur_user = temp_usr;
            printf("Login to user %s successful.\n", cur_user -> name);
            break;
        case 2:
            if(!(cur_user -> id)){
                printf("error: You are not logged in as a user!\n");
                return TRUE;
            }
            cur_user = user_head;
            printf("Logout successful.\n");
            break;
        case 3:
            x_id = find_by_user_name(user_head, words[1]);
            if(x_id == 0){
                printf("error: User does not exist!\n");
                return TRUE;
            }
            /* retrieve posts and print them */
            temp_posts = find_posts_from_user(post_head, x_id);
            printf("Username: %s\n", words[1]);
            printf("Posts:\n");
            write_posts(temp_posts);
            free(temp_posts);
            break;
        case 4:
            if(!(cur_user -> id)){
                printf("error: You can't post when you are not logged in!\n");
                return TRUE;
            }
            post* npost = create_new_post(post_head, &post_id_cnt, cur_user -> id, words[1]);
            CHECK_MAL(npost);
            cur_user -> post_cnt++;
            printf("Post successful.\n");
            break;
        case 5:
            /* check whether the second word is a positive integer */
            if(!is_pos_int(words[1]) || !atoi(words[1])){
                printf("error: Post ID must be a positive integer!\n");
                return TRUE;
            }
            y_id = atoi(words[1]);
            if(!(cur_user -> id)){
                printf("error: You can't delete posts when you are not logged in!\n");
                return TRUE;
            }
            if(!is_post_from_user(post_head, y_id, cur_user -> id)){
                printf("error: You don't have a post with id %d\n", y_id);
                return TRUE;
            }
            delete_by_post_id(like_head, y_id);
            delete_post(post_head, y_id);
            printf("Post was deleted succesfully.\n");
            (cur_user -> post_cnt)--;
            break;
        case 6:
            if(!(cur_user -> id)){
                printf("error: You're not logged in as a user!\n");
                return TRUE;
            }
            /* retrieve current user's info */
            printf("Username: %s\n", cur_user -> name);
            printf("Password: %s\n", cur_user -> pass);
            printf("Number of posts: %d\n", cur_user -> post_cnt);
            temp_posts = find_posts_from_user(post_head, cur_user -> id);
            write_posts(temp_posts);
            free(temp_posts);
            break;
        case 7:
            /* whether the second word is a positive integer */
            if(!is_pos_int(words[2]) || !atoi(words[2])){
                printf("error: Post ID must be a positive integer!\n");
                return TRUE;
            }
            y_id = atoi(words[2]);
            x_id = find_by_user_name(user_head, words[1]);
            if(!x_id){
                printf("error: User %s does not exist!\n", words[1]);
                return TRUE;
            }
            if(!(cur_user -> id)){
                printf("error: You can't like posts when you'r not logged in!\n");
                return TRUE;
            }
            if(!is_post_from_user(post_head, y_id, x_id)){
                printf("error: User %s does not have a post with the id %d!\n", words[1], y_id);
                return TRUE;
            }
            if(!new_like(like_head, &like_id_cnt, cur_user -> id, y_id)){
                printf("error: You've already liked this post!\n");
                return TRUE;
            }
            add_post_like_cnt(post_head, y_id, 1);
            printf("Like successful.\n");
            break;
        case 8:
            /* returns false condition so the while in main would break */
            printf("Exit command successful.\n");
            return FALSE;
        case 9:
            /* check for positive int */
            if(!is_pos_int(words[2]) || !atoi(words[2])){
                printf("error: Post ID must be a positive integer!\n");
                return TRUE;
            }
            y_id = atoi(words[2]);
            x_id = find_by_user_name(user_head, words[1]);
            if(!x_id){
                printf("error: User %s does not exist!\n", words[1]);
                return TRUE;
            }
            if(!(cur_user -> id)){
                printf("error: You can't unlike posts when you'r not logged in!\n");
                return TRUE;
            }
            if(!is_post_from_user(post_head, y_id, x_id)){
                printf("error: User %s does not have a post with the id %d!\n", words[1], y_id);
                return TRUE;
            }
            if(!delete_like(like_head, find_like(like_head, cur_user -> id, y_id))){
                printf("error: You have not liked this post!\n");
                return TRUE;
            }
            add_post_like_cnt(post_head, y_id, -1);
            printf("Unlike successful.\n");
            break;
        /* invalid command */
        default:
            printf("error: Invalid command name or wrong number of arguments!\n");
            return TRUE;
    }
    return TRUE;
}

int main(){
    char *cmd, **words;
    int words_sz;
    user_head = cur_user = initialize_user_linked_list(&user_id_cnt);
    post_head = initialize_post_linked_list(&post_id_cnt);
    like_head = initialize_like_linked_list(&like_id_cnt);
    int condition = TRUE; /* loop condition */
    while(condition){
        read_command(&cmd, &words);
        words_sz = words_size(words);
        /* empty line */
        if(!words_sz){
            free(words);
            free(cmd);
            continue;
        }
        condition = process(words, words_sz);
        free(words);
        free(cmd);
    }
    /* store gathered data */
    store_user_linked_list(user_head);
    store_post_linked_list(post_head);
    store_like_linked_list(like_head);
    /* free all allocated memory */
    clear_post_linked_list(post_head);
    clear_user_linked_list(user_head);
    clear_like_linked_list(like_head);
}
