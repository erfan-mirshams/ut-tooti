#include "general.h"
#include "struct.h"
#include "like.h"
#include "in-out.h"

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

/* creates a new head and returns it. also reads previous entries from file */
like *initialize_like_linked_list(int *cnt){
    like* head = (like *)malloc(sizeof(like));
    CHECK_MAL(head);
    head -> id = 0;
    head -> user_id = 0;
    head -> post_id = 0;
    head -> next = NULL;
    int id, user_id, post_id;
    FILE *db = fopen(LIKE_FILE, "r");
    if(db == NULL){
        return head;
    }
    while(TRUE){
        char *line, **words;
        line = read_line_from_file(db);
        words = split_words(line);
        int word_sz = words_size(words);
        if(!word_sz){
            free(line);
            free(words);
            break;
        }
        id = atoi(words[0]);
        user_id = atoi(words[1]);
        post_id = atoi(words[2]);
        *cnt = MAX(*cnt, id);
        id--;
        new_like(head, &id, user_id, post_id);
        free(line);
        free(words);
    }
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

/* each linked list entry in a single line */
int store_like_linked_list(like *head){
    FILE *db = fopen(LIKE_FILE, "w+");
    if(db == NULL){
        return FALSE;
    }
    for(head = head -> next; head != NULL; head = head -> next){
        fprintf(db, "%d %d %d\n", head -> id, head -> user_id, head -> post_id);
    }
    fclose(db);
    return TRUE;
}
