#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "hash.h"
#include "list.h"
#define ADR_CHECK if(current==NULL)           \
        {                                     \
            perror ( "invalid table addr\n" );\
            return 0;                         \
        }
#define KEY_CHECK if(key==NULL)\
        {                                       \
            perror ("invalid string pointer\n");\
            return 0;                           \
        }
#define FILE_CHECK if(!f)\
        return 0;

hashtable* constructor ( int size )
{
    if ( !size )
        return NULL;

    hashtable* ret = NULL; 
    list* value = NULL;
    ret = calloc( 1, sizeof ( hashtable ));
    value = calloc ( size, sizeof (list));
    if ( ret == NULL || value == NULL )
    {
        free ( ret );
        free ( value );
        return NULL;
    }
    ret -> size = size;
    ret -> counter = 0;
    ret -> heads = value;
    
   
    int i = 0;
    node* new = NULL;
    for ( i = 0; i < size - 1; i ++ )
    {
        new = calloc ( 1, sizeof ( node ));
        if ( new == NULL )
        {
            free ( ret -> heads );
            free ( ret );
            return NULL;
        }
        ret -> heads[i].head = new;
        ret -> heads[i].head -> hash = 0;
        strcpy ( ret -> heads[i].head -> key, "" );
        ret -> heads[i].head -> next = NULL;
        ret -> heads[i].head -> prev = NULL;
        ret -> heads[i].current = ret -> heads[i].head;
    }
    dump ( ret, "table created" );
    return ret;
}

int destructor ( hashtable* current )
{
    ADR_CHECK

    int i = 0;
    hashtable* value = current;
    for ( i = 0; i < current -> size - 1; i ++ )
    {
        delete_list ( &(current -> heads[i]) );
    }
    free ( current -> heads );
    free ( current );

    current = NULL;
    dump ( value, "table deleted" );
    return 1;
}

int calc ( const char* key )
{
    KEY_CHECK
    int i = 0;
    int ret = 0;
    
    while ( key[i] != 0 )
    {
        ret += key[i];
        i ++;
    }
    
    return ret;    
}

list* find_hash ( hashtable* current, int hash )
{
    ADR_CHECK
    int i = 0;
    list* ret = NULL;
    dump ( current, "search called" );
    for ( i = 0; i < current -> counter; i ++ )
    {
        if ( current -> heads[i].head -> hash == hash )
        {
            dump ( current, "search done" );
            return &(current -> heads[i]);
        }
    }
    
    dump ( current, "search failed" );
    return ret;    
}

list* new_head ( hashtable* current, int hash, const char* key )
{
    ADR_CHECK
    KEY_CHECK
    
    if ( current -> counter == current -> size - 2 )
    {
        perror ( "need reallocation\n");
        return NULL;
    }
    list* ret = &(current -> heads[current -> counter]);
    ret -> head -> hash = hash;
    strcpy ( ret -> head -> key, key );
    current -> counter += 1;
    dump ( current, "new head added" );
    return ret;
}

int add ( hashtable* current, const char* key )
{
    ADR_CHECK
    KEY_CHECK

    int hash = calc ( key );
   
    if ( !hash )
    {
        perror ( "unable to calc hash\n" );
        return 0;
    }    
    list* current_list = find_hash ( current, hash );
    if ( !current_list )
    {
        current_list = new_head ( current, hash, key );
        return 1;
    }
    else
    {
        node* ret = append ( current_list, hash, key );
        return 0;
    }

}

int delete_key ( hashtable* current, const char* key )
{
    ADR_CHECK
    KEY_CHECK

    int hash = calc ( key );
    int ret = -1;
    list* curlist = find_hash ( current, hash );
    if ( curlist != NULL )
        ret = delete_node ( curlist, key );
    dump ( current, "key deleted" );
    return ret;
}

node* search ( hashtable* current, const char* key )
{
    ADR_CHECK
    KEY_CHECK

    int hash = calc ( key );
    list* curlist = find_hash ( current, hash );
    if ( !curlist )
        return NULL;
    node* ret = find_node ( curlist, key );
    
    return ret;
}

int print ( const hashtable* current )
{
    ADR_CHECK
    FILE* f = fopen ( "table", "w" );
    FILE_CHECK
    int i = 0;
    node* victim = NULL;

    for ( i = 0; i < current -> counter; i ++ )
    {
        victim = current -> heads[i].head;
        fprintf ( f, "%d  ===  ", victim -> hash );
        fprintf ( f,  "%s ", victim -> key );
        victim = victim -> next;
        while ( victim != NULL )
        {
            fprintf ( f,  "         %s", victim -> key );
            victim = victim -> next;
        }
        fprintf ( f, "\n\n" );
    }
    
    fclose ( f );
}

int dump ( const hashtable* current, const char* message )
{
    if ( current == NULL )
    ;
    else if ( message == NULL )
    ;
    else
    {
        FILE* f = fopen ( "dump", "a" );
        FILE_CHECK
        fprintf ( f, "%p: ", current );
        fprintf ( f, "%s ", message );
        if ( strcmp ( message, "new head added" ) == 0 )
        {
            fprintf ( f, "number of heads = %d", current -> counter );
        }
        fprintf ( f, "\n" );
        fclose ( f );
    }
    
    return 0;    
}
}


