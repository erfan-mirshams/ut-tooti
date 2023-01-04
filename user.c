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
    nusr -> id = *id;
    string_fill(nusr -> name, name);
    string_fill(nusr -> pass, pass);
    nusr -> post_cnt = 0;
    nusr -> prev = head;
    nusr -> next = head -> next;
    head -> next = nusr;
    return TRUE;
}

user *initialize_user_linked_list(){
    user *head = (user *)malloc(sizeof(user));
    head -> id = 0;
    head -> name = head -> pass = "";
    head -> post_cnt = 0;
    head -> next = head -> prev = NULL;
    return head;
}

void clear_user_linked_list(user *head){
    user *nxt;
    for(; head != NULL; head = nxt){
        nxt = head -> next;
        free(head -> name);
        free(head -> pass);
        free(head);
    }
}
