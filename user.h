#ifndef USER_H_
#define USER_H_
#define USER_FILE "user.txt"
int find_by_user_name(user *head,char *name);
user *login(user *head, char *name, char *pass);
int signup(user *head, int *id, char *name, char *pass);
user *initialize_user_linked_list(int *cnt);
void clear_user_linked_list(user *head);
int store_user_linked_list(user *head);
#endif // USER_H_
