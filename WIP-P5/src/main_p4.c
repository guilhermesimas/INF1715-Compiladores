#include <stdio.h>
#include <stdlib.h>

#include "absSyntaxTree.h"
#include "astKnit.h"
#include "typeCheck.h"
#include "types.h"

#include "monga.tab.h"
#include "lex.h"

int main(void) {
	int ret;
	
	ret = yyparse();
	
	knitABS();
	
	typeCheckABS();
	
	ABS_print(2); // Bom manter aqui, para DEBUG
	
	BUF_Free();
	
	return ret;
}
