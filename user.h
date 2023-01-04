#ifndef USER_H_
#define USER_H_
int find_by_user_name(user *head,char *name);
user *login(user *head, char *name, char *pass);
int signup(user *head, int *id, char *name, char *pass);
user *initialize_user_linked_list();
#endif // USER_H_
