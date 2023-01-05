#include "general.h"
#include "struct.h"
#include "like.h"

int delete_by_post_id(like *head, int post_id){
    int flag = FALSE;
    like *prev = head;
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> post_id == post_id){
            prev -> next = head -> next;
            free(head);
            head = prev;
            flag = TRUE;
        }
        prev = head;
    }
    return flag;
}

int find_like(like *head, int user_id, int post_id){
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> user_id == user_id && head -> post_id == post_id){
            return head -> id;
        }
    }
    return 0;
}

int new_like(like *head, int *id, int user_id, int post_id){
    if(find_like(head, user_id, post_id)){
        return FALSE;
    }
    like *nlike = (like *)malloc(sizeof(like));
    CHECK_MAL(nlike);
    (*id)++;
    nlike -> id = *id;
    nlike -> user_id = user_id;
    nlike -> post_id = post_id;
    nlike -> next = head -> next;
    head -> next = nlike;
    return TRUE;
}

int delete_like(like *head, int id){
    like *prev = head;
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> id == id){
            prev -> next = head -> next;
            free(head);
            return TRUE;
        }
        prev = head;
    }
    return FALSE;
}

like *initialize_like_linked_list(){
    like* head = (like *)malloc(sizeof(like));
    CHECK_MAL(head);
    head -> id = 0;
    head -> user_id = 0;
    head -> post_id = 0;
    head -> next = NULL;
    return head;
}

void clear_like_linked_list(like *head){
    like *temp_like;
    for(; head != NULL; head = temp_like){
        temp_like = head -> next;
        free(head);
    }
}
