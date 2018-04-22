#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hash.h"

hashtable* constructor ( int size )
{
    if ( !size )
    {
        perror ( "constructor error" );
        return 0;
        }
    hashtable* ret = calloc ( size, sizeof ( hashtable ));
    if ( !ret )
    {
        perror ( "allocation error" );
        return 0;
    }
    ret -> size = size;
    ret -> heads = calloc ( size, sizeof (node));
    if ( !ret -> heads )
    {
        perror ( "allocation error" );
        return 0;
    }
    
    return ret;
}

int destructor ( hashtable* current )
{
    if ( current = NULL )
        return 0;
    int i = 0;
    for ( i = 0; i < current -> size; i ++ )
        delete_list ( current -> heads[i] );

    return 1;
}


