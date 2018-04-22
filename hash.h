#ifndef HASH_H_

#define HASH_H_

struct node 
{
    struct node* next;
    struct node* prev;
    char key[50];
    int hash;
};

typedef struct node node;


struct hashtable
{
    int size;
    node* heads;
};

typedef struct hashtable hashtable;

hashtable* constructor ( int size );
int destructor ( hashtable* current );
int insert ( hashtable* current, char* key );
int delete ( hashtable* current, char* key );
node* search ( hashtable* current, char* key );
int hashfunction ( char* key );






#endif /*HASH_H_*/
