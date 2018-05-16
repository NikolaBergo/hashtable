#ifndef HASH_H_

#define HASH_H_

#include "list.h"

struct hashtable
{
    int size;
    int counter;

    list* heads;
};

typedef struct hashtable hashtable;

int dump ( const hashtable* current, const char* message );
hashtable* constructor ( int size );
int destructor ( hashtable* current );
list* new_head ( hashtable* current, int hash, const char* key );
int add ( hashtable* current, const char* key );
int delete_key ( hashtable* current, const char* key );
node* search ( hashtable* current, const char* key );
int calc ( const char* key );
list* find_hash ( hashtable* current, int hash );
int print ( const hashtable* current );






#endif /*HASH_H_*/
