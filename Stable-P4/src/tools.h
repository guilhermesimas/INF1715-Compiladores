#ifndef TOOLS_HEADER
#define TOOLS_HEADER

void TOL_error(const char* msg , int line , const char* info );

void TOL_warning(const char* msg , int line , const char* info );

void TOL_typeError(const char* msg , int line , int type1 , int type2 );

void TOL_checkAlloc( void* flag , const char* auxMsg  , char* auxRef );


#endif
