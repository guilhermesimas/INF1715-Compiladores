#include <stdio.h>
#include <stdlib.h>

#include "monga.tab.h"
#include "lex.h"

#define _PRINT_ESCAPES 0

void stringRawPrint( char* str ) {
	int i = 0;
	
	#if _PRINT_ESCAPES == 1	
	while( str[i] != '\0' ) {
		switch( str[i] ) {
			case '\n':
				printf("\\n");
				break;
				
			case '\\':
				printf("\\");
				break;
				
			case '\t':
				printf("\\t");
				break;
				
			case '"':
				printf("\"");
				break;
		
			default:
				printf("%c",str[i]);
				break;
		}
		i++;
	}
	#else
	while( str[i] != '\0' ) {
		printf("%c",str[i]);
		i++;
	}
	#endif
}

void printFlavorToken( int TK ) {
	switch( TK ) {
		case TK_VOID:
			printf("\n%d: TK_VOID" , LEX_LineNumber ); break;
			
		case TK_CHAR:
			printf("\n%d: TK_CHAR" , LEX_LineNumber ); break;
			
		case TK_INT:
			printf("\n%d: TK_INT" , LEX_LineNumber ); break;
						
		case TK_FLOAT:
			printf("\n%d: TK_FLOAT" , LEX_LineNumber ); break;	
				
		case TK_IF:
			printf("\n%d: TK_IF" , LEX_LineNumber ); break;	
			
		case TK_ELSE:
			printf("\n%d: TK_ELSE" , LEX_LineNumber ); break;	
			
		case TK_WHILE:
			printf("\n%d: TK_WHILE" , LEX_LineNumber ); break;	
			
		case TK_NEW:
			printf("\n%d: TK_NEW" , LEX_LineNumber ); break;
				
		case TK_RETURN:
			printf("\n%d: TK_RETURN" , LEX_LineNumber ); break;	
			
		case TK_GE:
			printf("\n%d: TK_GE" , LEX_LineNumber ); break;	
			
		case TK_LE:
			printf("\n%d: TK_LE" , LEX_LineNumber ); break;	
			
		case TK_CE:
			printf("\n%d: TK_CE" , LEX_LineNumber ); break;	
			
		case TK_NE:
			printf("\n%d: TK_NE" , LEX_LineNumber ); break;
				
		case TK_AND:
			printf("\n%d: TK_AND" , LEX_LineNumber ); break;
							
		case TK_OR:
			printf("\n%d: TK_OR" , LEX_LineNumber ); break;	
			
		case TK_ID:
			printf("\n%d: TK_ID : %s" , LEX_LineNumber , LEX_seminfo.s ); break;	
			
		case TK_NUM_CHAR:
			printf("\n%d: TK_NUM_CHAR : %u" , LEX_LineNumber , LEX_seminfo.i); break;	
			
		case TK_NUM_INT:
			printf("\n%d: TK_NUM_INT : %d" , LEX_LineNumber , LEX_seminfo.i); break;	
			
		case TK_NUM_FLOAT:
			printf("\n%d: TK_NUM_FLOAT : %f" , LEX_LineNumber , LEX_seminfo.f); break;	
			
		case TK_STRING:
			printf("\n%d: TK_STRING : " , LEX_LineNumber ); 
			stringRawPrint( LEX_seminfo.s ); 
			break;				
			
		default:
			printf("\n%d: %c" , LEX_LineNumber , TK ); break;
	}
}

int main(void) {
	int ret;
	
	//char a[] = "aa\y\daa";
	//fprintf(stderr, "\n%s\y\n" , a );
	
	while( ( ret = yylex() ) && ret >= 0 ) {
		printFlavorToken( ret );		
	}

	BUF_Free();
	
	printf("\n\n");	
	return 0;
}
