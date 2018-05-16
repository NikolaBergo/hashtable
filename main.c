#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define SIZE 100

int main ()
{
    char buf[SIZE];
    hashtable* table = constructor (0);
    table = constructor ( 50 );
    
    FILE* f = fopen ( "example", "r" );
    while ( fgets ( buf, 99, f ) != 0 )
    {
        add ( table, buf );
    }
    add ( NULL, "yo" );
    fclose ( f );
    delete_key ( NULL, "pol" );
    delete_key ( table, "book" );
    delete_key ( table, "a\n" );
    delete_key ( table, "admire\n" );
    add ( table, "");
    search ( NULL, "gus" );
    search ( table, "abandon\n" );
    search ( table, "book");
    search ( table, "adjust\n" );
    search ( table, "affair\n" );
    print ( table );  
    print ( NULL );  
    destructor ( table );
    destructor ( NULL );
    dump ( NULL, "" );
    append ( NULL, 0, "" );
    find_node ( NULL, "" );
    calc ( NULL );
    
    return 0;
}
