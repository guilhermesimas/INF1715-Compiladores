#include "tools.h"
#include "monga.tab.h"
#include "lex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _SHOW_WARNINGS 1


void TOL_print_dataType( int type );


// Generic Error message
void TOL_error(const char* msg , int line , const char* info ) {	
	fprintf(stderr, "\n\x1B[91mERROR: line %d: %s" , line , msg );
	
	if( info )
		fprintf(stderr, ": %s" , info );
		
	fprintf(stderr, "\x1B[0m\n" );
		
	exit(1);
}

// Type error message
void TOL_typeError(const char* msg , int line , int type1 , int type2 ) {	
	fprintf(stderr, "\n\x1B[91mERROR: line %d: %s:\n" , line , msg );
	
	fprintf(stderr, "type 1: " );
	TOL_print_dataType(type1);
	
	fprintf(stderr, " | type 2: " );
	TOL_print_dataType(type2);	
		
	fprintf(stderr, "\x1B[0m\n" );
		
	exit(1);
}

// Warning message
void TOL_warning(const char* msg , int line , const char* info ) {	
	#if _SHOW_WARNINGS == 0
		return;
	#endif

	fprintf(stderr, "\n\x1B[36mWARNING: line %d: %s" , line , msg );
	
	if( info )
		fprintf(stderr, ": %s" , info );
		
	fprintf(stderr, "\x1B[0m\n" );
}

// Check Allocation
void TOL_checkAlloc( void* flag , const char* auxMsg  , char* auxRef ) {
	if( flag == NULL ) {
		fprintf(stderr, "\n\x1B[91mAllocation Error: %s" , auxMsg );
		
		if( auxRef != NULL ) {
			fprintf(stderr, "%s" , auxRef );
		}

		fprintf(stderr, "\x1B[0m\n" );
		exit(1);
	}
}

// Auxiliary Functions

void TOL_print_dataType( int type ) {
	int dim = 0;
	int i;

	fprintf(stderr,"<");
	
	if ( type < 0 ) {
		fprintf(stderr,"Unknown>");
		return;
	}
	else if ( type >= TYPEQTY ) { 
		while( type >= TYPEQTY ) {
			dim++;
			type -= TYPEQTY;
		}
	}

	switch( type ) {
		case CHAR:
			fprintf(stderr,"Char");
			break;
		case INT:
			fprintf(stderr,"Integer");
			break;
		case FLOAT:
			fprintf(stderr,"Float");
			break;
		case VOID:
			fprintf(stderr,"Void");
			break;
	}
	
	for( i = 0 ; i < dim ; i++ ) {
		fprintf(stderr,"[]");
	}
	
	fprintf(stderr,">");
}
