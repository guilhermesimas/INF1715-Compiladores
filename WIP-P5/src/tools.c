#include "tools.h"
#include "monga.tab.h"
#include "lex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _SHOW_WARNINGS 1

// Error message
void TOL_error(const char* msg , int line , const char* info ) {	
	fprintf(stderr, "\n\x1B[91mERROR: line %d: %s" , line , msg );
	
	if( info )
		fprintf(stderr, ": %s" , info );
		
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
