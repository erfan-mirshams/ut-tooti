#include "general.h"
#include "in-out.h"
#include "struct.h"
#include "user.h"


/* static variables */
static user *user_head, *cur_user;
static int user_id_cnt;

/* reads a line into ch and splits the words into words */
void read_command(char **ch, char ***words){
    *ch = read_line();
    *words = split_words(*ch);
}

/* processes the command */
int process(char **words, int sz){
    char *command_names[] = {"signup", "login", "logout", "find_user", "post", "delete", "info", "like", "exit"};
    int command_input_size[] = {3, 3, 1, 2, -1, 2, 1, 2, 1};
    int command_id = -1, i;
    for(i = 0; i < COMMAND_CNT; i++){
        /* if the command is valid */
        if(!strcmp(*words, command_names[i]) && (sz == command_input_size[i] || command_input_size[i] == -1)){
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
            printf("Signup successful\n");
            break;
        case 8:
            printf("Exit command successful\n");
            return FALSE;
        default:
            printf("error: Invalid command name or wrong number of arguments!\n");
            return TRUE;
    }
    return TRUE;
}

int main(){
    char *cmd, **words;
    user *cur_user;
    int words_sz;
    user_head = cur_user = initialize_user_linked_list();
    user_id_cnt = 0;
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
    clear_user_linked_list(user_head);
}
