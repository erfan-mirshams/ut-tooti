#include "general.h"
#include "in-out.h"
#include "struct.h"
#include "user.h"
#include "post.h"


/* static variables */
static user *user_head, *cur_user;
static int user_id_cnt, post_id_cnt;
static post *post_head;

/* reads a line into ch and splits the words into words */
void read_command(char **ch, char ***words){
    *ch = read_line();
    *words = split_words(*ch);
}

/* processes the command */
int process(char **words, int sz){
    char *command_names[] = {"signup", "login", "logout", "find_user", "post", "delete", "info", "like", "exit"};
    int command_input_size[] = {3, 3, 1, 2, 2, 2, 1, 2, 1};
    int command_id = -1, i;
    for(i = 0; i < COMMAND_CNT; i++){
        /* if the command is valid */
        if(!strcmp(*words, command_names[i]) && sz == command_input_size[i]){
            command_id = i;
            continue;
        }
    }

    /* if invalid command name or number of arguments */
    switch (command_id) {
        case 0:
            if(!signup(user_head, &user_id_cnt, words[1], words[2])){
                printf("error: This username is taken!\n");
                return TRUE;
            }
            cur_user = login(user_head, words[1], words[2]);
            printf("Signup successful. User %s created.\n", cur_user -> name);
            break;
        case 1:
            user *temp_usr;
            temp_usr = login(user_head, words[1], words[2]);
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
        case 4:
            if(!(cur_user -> id)){
                printf("error: You can't post when you are not logged in!\n");
                return TRUE;
            }
            post* npost = create_new_post(post_head, &post_id_cnt, cur_user -> id, words[1]);
            if(npost == NULL){
                mal_fail();
            }
            printf("Post successful.\n");
            break;
        case 8:
            printf("Exit command successful.\n");
            return FALSE;
        default:
            printf("error: Invalid command name or wrong number of arguments!\n");
            return TRUE;
    }
    return TRUE;
}

int main(){
    char *cmd, **words;
    int words_sz;
    user_head = cur_user = initialize_user_linked_list();
    post_head = initialize_post_linked_list();
    post_id_cnt = user_id_cnt = 0;
    int condition = TRUE; /* loop condition */
    while(condition){
        printf("DEBUG:\n");
        read_command(&cmd, &words);
        printf("VALLA\n");
        words_sz = words_size(words);
        /* empty line */
        if(!words_sz){
            continue;
        }
        printf("WORDSZ: %d\n", words_sz);
        condition = process(words, words_sz);
        free(words);
        free(cmd);
    }
    printf("FIN\n");
    clear_post_linked_list(post_head);
    clear_user_linked_list(user_head);
}
