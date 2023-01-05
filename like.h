#ifndef LIKE_H_
#define LIKE_H_
like *initialize_like_linked_list();
void clear_like_linked_list(like *head);
int find_like(like *head, int user_id, int post_id);
int new_like(like *head, int *id, int user_id, int post_id);
int delete_like(like *head, int id);
#endif // LIKE_H_
