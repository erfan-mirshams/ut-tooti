#ifndef POST_H_
#define POST_H_
post *initialize_post_linked_list();
void clear_post_linked_list(post *head);
post *create_new_post(post *head, int *id, int user_id, char *content);
post **find_posts_from_user(post *head, int user_id);
int is_valid_post(post *head, int id);
int is_post_from_user(post *head, int id, int user_id);
int add_post_like_cnt(post *head, int id, int val);
int delete_post(post *head, int id);
#endif // POST_H_
