#ifndef POST_H_
#define POST_H_
post *initialize_post_linked_list();
void clear_post_linked_list(post *head);
post *create_new_post(post *head, int *id, int user_id, char *content);
post **find_posts_from_user(post *head, int user_id);
#endif // POST_H_
