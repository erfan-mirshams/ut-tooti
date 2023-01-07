#include "general.h"
#include "struct.h"
#include "post.h"

/* delete single post node based on id */
int delete_post(post *head, int id){
    post *prev = head;
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> id == id){
            prev -> next = head -> next;
            free(head -> content);
            free(head);
            return TRUE;
        }
        prev = head;
    }
    return FALSE;
}

/* returns all the posts by a certain user */
post **find_posts_from_user(post *head, int user_id){
    post **posts = (post **)malloc(sizeof(post*));
    CHECK_MAL(posts);
    *posts = NULL;
    int i = 0;
    for(head = head -> next; head != NULL; head = head -> next){
        /* Add new post pointer to the entry */
        if(head -> user_id == user_id){
            posts = (post **)realloc(posts, sizeof(post*) * (i + 2));
            CHECK_MAL(posts);
            posts[i + 1] = NULL;
            posts[i++] = head;
        }
    }
    return posts;
}

/* checks whether a certain user does have a post with a certain id */
int is_post_from_user(post *head, int id, int user_id){
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> id == id && head -> user_id == user_id){
            return TRUE;
        }
    }
    return FALSE;
}

/* whether the post id exists in the linked list */
int is_valid_post(post *head, int id){
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> id == id){
            return TRUE;
        }
    }
    return FALSE;
}

/* increments like count of a single node the amount of val */
int add_post_like_cnt(post *head, int id, int val){
    for(head = head -> next; head != NULL; head = head -> next){
        if(head -> id == id){
            (head -> like_cnt) += val;
            return TRUE;
        }
    }
    return FALSE;
}

/* creates a new post and inserts it next to the head of the linked list */
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

/* creates a new head and returns it. also reads previous entries from file */
post *initialize_post_linked_list(int *cnt){
    post *head = (post *)malloc(sizeof(post));
    CHECK_MAL(head);
    *cnt = head -> id = 0;
    head -> user_id = 0;
    head -> like_cnt = 0;
    head -> content = (char *)malloc(sizeof(char));
    CHECK_MAL(head -> content);
    *(head -> content) = '\0';
    head -> next = NULL;
    FILE *db = fopen(POST_FILE, "r");
    if(db == NULL){
        return head;
    }
    char *content;
    int id, user_id, like_cnt;
    content = (char *)malloc(sizeof(char) * MAXN);
    CHECK_MAL(content);
    while(TRUE){
        if(fscanf(db, "%d %d %d %s", &id,  &user_id, &like_cnt, content) != 4){
            break;
        }
        *cnt = MAX(*cnt, id);
        /* because create_new_post increments id */
        id--;
        create_new_post(head, &id, user_id, content);
        add_post_like_cnt(head, id, like_cnt);
    }
    free(content);
    return head;
}

/* clears linked list and deallocated memory for nodes and the strings within */
void clear_post_linked_list(post *head){
    post *temp_post;
    for(; head != NULL; head = temp_post){
        temp_post = head -> next;
        free(head -> content);
        free(head);
    }
}

/* each linked list entry in a single line */
int store_post_linked_list(post *head){
    FILE *db = fopen(POST_FILE, "w+");
    if(db == NULL){
        return FALSE;
    }
    for(head = head -> next; head != NULL; head = head -> next){
        fprintf(db, "%d %d %d %s\n", head -> id, head -> user_id, head -> like_cnt, head -> content);
    }
    fclose(db);
    return TRUE;
}
