#ifndef LIST_H_

#define LIST_H_

#define KEY_SIZE 100

struct node 
{
    struct node* next;
    struct node* prev;
    char key[KEY_SIZE];
    int hash;
};

typedef struct node node;

struct list
{
    node* current;
    node* head;
};

typedef struct list list;

int delete_list ( list* current );
int delete_node ( list* current, const char* key );
node* append ( list* current, int hash, const char* key );
node* find_node ( list* current, const char* key );





#endif
