#include <stdio.h>
#include <stdlib.h>

#include "absSyntaxTree.h"
#include "types.h"

#include "monga.tab.h"
#include "lex.h"

int main(void) {
	int ret;
	
	ret = yyparse();
	
	ABS_print(1);
	
	BUF_Free();
	
	return ret;
}
