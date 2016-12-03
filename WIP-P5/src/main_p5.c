#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "absSyntaxTree.h"
#include "astKnit.h"
#include "typeCheck.h"
#include "types.h"
#include "llvm.h"

#include "monga.tab.h"
#include "lex.h"

int main(int argc, char **argv) {
	int ret = 0;
	
	// Lex and Yacc
	ret = yyparse();
	
	// knit Abstract Syntax Tree
	knitABS();
	
	// Typecheck
	typeCheckABS();
	
	// Print tree
	if( argc > 1 && strcmp( argv[1] , "debug" ) == 0 ) {
		ABS_print(2);
	}

	// Label
	if( argc > 1 && strcmp( argv[1] , "debug" ) == 0 ) {	
		printf("\nCODE GENERATED\n");
	}
	
	// Generate Code
	genASTCode();
	
	// Free Buffers
	BUF_Free();
	
	return ret;
}
