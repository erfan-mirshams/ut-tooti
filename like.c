#include "general.h"
#include "struct.h"
#include "like.h"

/* deletes all the likes with the given post id */
int delete_by_post_id(like *head, int post_id){
    int flag = FALSE;
    like *prev = head;
    for(head = head -> next; head != NULL; head = head -> next){
        /* removes the current node and rolls back to the previous node */
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

/* finds the id of a like with certain user and post id */
int find_like(like *head, int user_id, int post_id){
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> user_id == user_id && head -> post_id == post_id){
            return head -> id;
        }
    }
    return 0;
}

/* creates new like node and inserts it next to the head of the linked list */
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

/* deletes on like node by id */
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

/* creates a new head and returns it */
like *initialize_like_linked_list(){
    like* head = (like *)malloc(sizeof(like));
    CHECK_MAL(head);
    head -> id = 0;
    head -> user_id = 0;
    head -> post_id = 0;
    head -> next = NULL;
    return head;
}

/* delete all nodes and free the allocated memory */
void clear_like_linked_list(like *head){
    like *temp_like;
    for(; head != NULL; head = temp_like){
        temp_like = head -> next;
        free(head);
    }
}
