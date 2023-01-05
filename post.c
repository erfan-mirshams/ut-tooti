#include "general.h"
#include "struct.h"
#include "post.h"

post *create_new_post(post *head, int *id, int user_id, char *content){
    (*id)++;
    post *npost = (post *)malloc(sizeof(post));
    CHECK_MAL(npost);
    npost -> id = *id;
    npost -> user_id = user_id;
    npost -> like_cnt = 0;
    npost -> content = string_fill(content);
    npost -> next = head -> next;
    head -> next = npost;
    return npost;
}

post *initialize_post_linked_list(){
    post *head = (post *)malloc(sizeof(post));
    CHECK_MAL(head);
    head -> id = 0;
    head -> user_id = 0;
    head -> like_cnt = 0;
    head -> content = (char *)malloc(sizeof(char));
    CHECK_MAL(head -> content);
    *(head -> content) = '\0';
    head -> next = NULL;
    return head;
}

void clear_post_linked_list(post *head){
    post *temp_post;
    for(; head != NULL; head = temp_post){
        temp_post = head -> next;
        free(head -> content);
        free(head);
    }
}
