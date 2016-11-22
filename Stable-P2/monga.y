%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(char *);
%}

%token	TK_VOID
%token	TK_CHAR
%token	TK_INT
%token	TK_FLOAT
%token	TK_IF
%token	TK_ELSE
%token	TK_WHILE
%token	TK_NEW
%token	TK_RETURN
%token	TK_GE
%token	TK_LE
%token	TK_CE
%token	TK_NE
%token	TK_AND
%token	TK_OR
%token	TK_ID
%token	TK_NUM_CHAR
%token	TK_NUM_INT
%token	TK_NUM_FLOAT
%token	TK_STRING

%nonassoc WO_ELSE
%nonassoc TK_ELSE

%%

program:	
	declarationChain	{;}
	;
	
primitiveType:
	TK_CHAR		{;}
	| TK_INT	{;}
	| TK_FLOAT	{;}
	;
	
type:
	primitiveType		{;}
	| type '[' ']'		{;}
	;
	
idList:
	TK_ID					{;}
	| idList ',' TK_ID		{;}
	;		

variableDeclaration:
	type idList ';'			{;}
	;
	
variableDeclarationChain:
	variableDeclarationChain variableDeclaration	{;}
	|	{;}
	;	

variable:
	TK_ID							{;}
	| expBase '[' expLogic ']' 		{;}
	;
	
expBase:
	TK_NUM_INT						{;}
	| TK_NUM_FLOAT 					{;}
	| TK_STRING						{;}
	| variable						{;}
	| '(' expLogic ')'  			{;}
	| cmdCall						{;}
	| TK_NEW type '[' expLogic ']'	{;}
	;

expUnary:
	expBase						{;}
	| '-' expBase				{;}
	| '!' expBase				{;}
	;
	
expMultOps:
	'*'			{;}
	| '/'		{;}
	;

expMult:
	expUnary	{;}
	| expMult expMultOps expUnary	{;}
	;
	
expAddOps:
	'+'			{;}
	| '-'		{;}
	;
	
expAdd:
	expMult		{;}
	| expAdd expAddOps expMult	{;}
	;
	
expCmpOps:
	TK_CE		{;}
	| TK_NE		{;}
	| TK_GE		{;}
	| TK_LE		{;}
	| '>'		{;}
	| '<'		{;}
	;
	
expCmp:
	expAdd		{;}
	| expCmp expCmpOps expAdd	{;}
	;
	
expAnd:
	expCmp		{;}
	| expAnd TK_AND expCmp {;}
	;
	
expLogic:
	expAnd					{;}
	| expLogic TK_OR expAnd	{;}
	;
	
expressionList:
	expressionListNonEmpty	{;}
	| 						{;}
	;
	
expressionListNonEmpty:
	expLogic				{;}
	| expressionListNonEmpty ',' expLogic {;}
	;
	
cmdCall:
	TK_ID '(' expressionList ')'			{;}
	;
	
cmdReturn:
	TK_RETURN	{;}
	| TK_RETURN expLogic {;}
	;
	
command:
	block							{;}
	| expLogic ';'					{;}
	| cmdReturn ';'					{;}	
	| variable '=' expLogic ';'		{;}
	| TK_WHILE '(' expLogic ')' command					{;}
	| TK_IF '(' expLogic ')' command %prec WO_ELSE    	{;}
	| TK_IF '(' expLogic ')' command TK_ELSE command    {;}
	;
	
commandChain:
	commandChain command		{;}
	|							{;}
	;

block:
	'{' variableDeclarationChain commandChain '}'		{;}
	;

argument:
	type TK_ID			{;}
	;
	
argumentList:
	argumentListNonEmpty	{;}
	| 						{;}
	;
	
argumentListNonEmpty:
	argument							{;}
	| argumentList ',' argument 		{;}
	;
	
functionSignature:
	TK_ID '(' argumentList ')' block 	{;}
	;
	
functionDeclaration:
	type functionSignature	{;}
	| TK_VOID functionSignature	{;}	
	;

declaration:
	variableDeclaration		{;}
	| functionDeclaration 	{;}
	;	
	
declarationChain:
	declarationChain declaration	{;}
	|								{;}
	;
			
%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}
