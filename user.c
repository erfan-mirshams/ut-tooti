#include "general.h"
#include "struct.h"

user *find_by_user_name(user *head,char *user_name){
    while(head != NULL){
        if (strcmp(head -> name, user_name)) {
            return head;
        }
        head++;
    }
    return NULL;
}
