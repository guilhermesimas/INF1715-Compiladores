#include <stdio.h>
#include <stdlib.h>

#include "monga.tab.h"
#include "lex.h"

int main(void) {
	int ret;
	
	ret = yyparse();
	
	BUF_Free();
	
	return ret;
}
