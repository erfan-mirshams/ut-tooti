#ifndef LIKE_H_
#define LIKE_H_
#define LIKE_FILE "like.txt"
#include <stdio.h>
like *initialize_like_linked_list(int *cnt);
void clear_like_linked_list(like *head);
int find_like(like *head, int user_id, int post_id);
int new_like(like *head, int *id, int user_id, int post_id);
int delete_like(like *head, int id);
int delete_by_post_id(like *head, int post_id);
int store_like_linked_list(like *head);
#endif // LIKE_H_
