%code requires {
	#include "absSyntaxTree.h"	
	#include "astKnit.h"	
	#include "types.h"
}

%code {
	#include <stdio.h>
		
	int yylex(void);
	void yyerror(char *);
	
	ABS_node* programNode = NULL;
}

%{

%}


%union {
    char* 	vString;
    int 	vInt;	
    float 	vFloat;
 
    struct id {
        char* 	name;
        int 	lineNumber;
    } vId;

    ABS_node* vNode;	
}

%token 	<vInt> 		TK_VOID
%token	<vInt> 		TK_CHAR
%token	<vInt> 		TK_INT
%token	<vInt> 		TK_FLOAT
%token	<vInt> 		TK_IF
%token	<vInt> 		TK_ELSE
%token	<vInt> 		TK_WHILE
%token	<vInt> 		TK_NEW
%token	<vInt> 		TK_RETURN
%token	<vInt> 		TK_GE
%token	<vInt> 		TK_LE
%token	<vInt> 		TK_CE
%token	<vInt> 		TK_NE
%token	<vInt> 		TK_AND
%token	<vInt> 		TK_OR
%token	<vId> 		TK_ID
%token	<vInt> 		TK_NUM_CHAR
%token	<vInt> 		TK_NUM_INT
%token	<vFloat> 	TK_NUM_FLOAT
%token	<vString>	TK_STRING

%nonassoc WO_ELSE
%nonassoc TK_ELSE


%type <vInt> primitiveType type 

%type <vNode> program idList variableDeclaration variableDeclarationChain variable
%type <vNode> expBase expUnary expMult expAdd expCmp expAnd expLogic 
%type <vNode> expressionList expressionListNonEmpty cmdCall cmdReturn command commandChain 
%type <vNode> block parameter parameterList parameterListNonEmpty
%type <vNode> functionDeclaration declaration declarationChain

%%

program:	
	declarationChain	{ programNode = $$; }
	;
	
primitiveType:
	TK_CHAR		{ $$ = TYP_getID( INT ); }
	| TK_INT	{ $$ = TYP_getID( INT ); }
	| TK_FLOAT	{ $$ = TYP_getID( FLOAT ); }
	;
	
type:
	primitiveType		{ $$ = $1; }
	| type '[' ']'		{ $$ = TYP_array($1); }
	;
	
idList:
	TK_ID					{ $$ = ABS_id($1.name , $1.lineNumber); }
	| idList ',' TK_ID		{ $$ = ABS_mergeList($1, ABS_id($3.name , $3.lineNumber)); }
	;		

variableDeclaration:
	type idList ';'			{ $$ = ABS_declVar($1, $2); }
	;
	
variableDeclarationChain:
	variableDeclarationChain variableDeclaration	{ $$ = ABS_mergeList($1, $2); }
	|	{ $$ = NULL; }
	;	

variable:
	TK_ID							{ $$ = ABS_varMono( ABS_id($1.name , $1.lineNumber) ); } 
	| expBase '[' expLogic ']' 		{ $$ = ABS_varArray($1, $3 ); }
	;
	
expBase:
	TK_NUM_INT						{ $$ = ABS_literalInt($1); } 
	| TK_NUM_FLOAT 					{ $$ = ABS_literalFloat($1); }
	| TK_STRING						{ $$ = ABS_literalString($1); }
	| variable						{ $$ = ABS_expVar($1); }
	| '(' expLogic ')'  			{ $$ = ABS_expParented($2); }
	| cmdCall						{ $$ = $1; }
	| TK_NEW type '[' expLogic ']'	{ $$ = ABS_expNew($2, $4); }
	;

expUnary:
	expBase						{ $$ = $1; }
	| '-' expBase				{ $$ = ABS_expOpr('-', $2, NULL); }
	| '!' expBase				{ $$ = ABS_expOpr('!', $2, NULL); }
	;

expMult:
	expUnary	{ $$ = $1; }
	| expMult '*' expUnary	{ $$ = ABS_expOpr('*', $1, $3); }
	| expMult '/' expUnary	{ $$ = ABS_expOpr('/', $1, $3); }	
	;
	
expAdd:
	expMult		{ $$ = $1; }
	| expAdd '+' expMult	{ $$ = ABS_expOpr('+', $1, $3); }
	| expAdd '-' expMult	{ $$ = ABS_expOpr('-', $1, $3); }
	;
	
expCmp:
	expAdd					{ $$ = $1; }
	| expCmp TK_CE expAdd	{ $$ = ABS_expOpr(TK_CE, $1, $3); }
	| expCmp TK_NE expAdd	{ $$ = ABS_expOpr(TK_NE, $1, $3); }
	| expCmp TK_GE expAdd	{ $$ = ABS_expOpr(TK_GE, $1, $3); }
	| expCmp TK_LE expAdd	{ $$ = ABS_expOpr(TK_LE, $1, $3); }
	| expCmp '>' expAdd		{ $$ = ABS_expOpr('>', $1, $3); }
	| expCmp '<' expAdd		{ $$ = ABS_expOpr('<', $1, $3); }				
	;
	
expAnd:
	expCmp					{ $$ = $1; }
	| expAnd TK_AND expCmp 	{ $$ = ABS_expOpr(TK_AND, $1, $3); }	
	;
	
expLogic:
	expAnd					{ $$ = $1; }
	| expLogic TK_OR expAnd	{ $$ = ABS_expOpr(TK_OR, $1, $3); }
	;
	
expressionList:
	expressionListNonEmpty	{ $$ = $1; }
	| 						{ $$ = NULL; }
	;
	
expressionListNonEmpty:
	expLogic								{ $$ = $1; }
	| expressionListNonEmpty ',' expLogic 	{ $$ = ABS_mergeList($1, $3); }
	;
	
cmdCall:
	TK_ID '(' expressionList ')'			{ $$ = ABS_expCall( ABS_id($1.name,$1.lineNumber) , $3); }
	;
	
cmdReturn:
	TK_RETURN				{ $$ = ABS_cmdRet(NULL); }
	| TK_RETURN expLogic 	{ $$ = ABS_cmdRet($2); }
	;
	
command:
	block							{ $$ = $1; }
	| expLogic ';'					{ $$ = ABS_cmdExp($1); }
	| cmdReturn ';'					{ $$ = $1; }
	| variable '=' expLogic ';'							{ $$ = ABS_cmdAttr($1, $3); }
	| TK_WHILE '(' expLogic ')' command					{ $$ = ABS_cmdWhile($3, $5); }
	| TK_IF '(' expLogic ')' command %prec WO_ELSE    	{ $$ = ABS_cmdIf($3, $5, NULL); }
	| TK_IF '(' expLogic ')' command TK_ELSE command    { $$ = ABS_cmdIf($3, $5, $7); }
	;
	
commandChain:
	commandChain command		{ $$ = ABS_mergeList($1, $2); }
	|							{ $$ = NULL; }
	;

block:
	'{' variableDeclarationChain commandChain '}'		{ $$ = ABS_block($2, $3); }
	;

parameter:
	type TK_ID			{ $$ = ABS_declVar($1, ABS_id($2.name,$2.lineNumber)); }
	;
	
parameterList:
	parameterListNonEmpty	{ $$ = $1; }
	| 						{ $$ = NULL; } 
	;
	
parameterListNonEmpty: 
	parameter							{ $$ = $1; }
	| parameterList ',' parameter 		{ $$ = ABS_mergeList($1, $3); }
	;
	
functionDeclaration:
	type TK_ID '(' parameterList ')' block 					{ $$ = ABS_declFunc($1, ABS_id($2.name,$2.lineNumber), $4, $6); } 
	| TK_VOID TK_ID '(' parameterList ')' block				{ $$ = ABS_declFunc( TYP_getID( VOID ) , ABS_id($2.name,$2.lineNumber), $4, $6); } 
	;

declaration:
	variableDeclaration		{ $$ = $1; } 
	| functionDeclaration 	{ $$ = $1; } 
	;	
	
declarationChain:
	declarationChain declaration	{ $$ = ABS_mergeList($1, $2); }
	|								{ $$ = NULL; } 
	;
			
%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}
