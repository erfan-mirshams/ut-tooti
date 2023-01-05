#include "general.h"
#include "struct.h"
#include "user.h"

int find_by_user_name(user *head,char *name){
    for(head = head -> next; head != NULL; head = head -> next){
        if(!strcmp(head  -> name, name)){
            return head -> id;
        }
    }
    return 0;
}

user *login(user *head, char *name, char *pass){
    for(head = head -> next; head != NULL; head = head -> next){
        if(!strcmp(head -> name, name) && !strcmp(head -> pass, pass)){
            return head;
        }
    }
    return NULL;
}

int signup(user *head, int *id, char *name, char *pass){
    if(find_by_user_name(head, name)) {
        return FALSE;
    }
    (*id)++;
    user *nusr = (user *)malloc(sizeof(user));
    CHECK_MAL(nusr);
    nusr -> id = *id;
    nusr -> name = string_fill(name);
    nusr -> pass = string_fill(pass);
    nusr -> post_cnt = 0;
    nusr -> next = head -> next;
    head -> next = nusr;
    return TRUE;
}

user *initialize_user_linked_list(){
    user *head = (user *)malloc(sizeof(user));
    CHECK_MAL(head);
    head -> id = 0;
    head -> name = (char *)malloc(sizeof(char));
    CHECK_MAL(head -> name);
    head -> pass = (char *)malloc(sizeof(char));
    CHECK_MAL(head -> pass);
    *(head -> name) = *(head -> pass) = '\0';
    head -> post_cnt = 0;
    head -> next = NULL;
    return head;
}

void clear_user_linked_list(user *head){
    user *temp_usr;
    for(; head != NULL; head = temp_usr){
        temp_usr = head -> next;
        free(head -> name);
        free(head -> pass);
        free(head);
    }
}
