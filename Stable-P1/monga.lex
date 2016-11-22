%option noyywrap

DIGITS		([1-9][0-9]*)|0
BLANK		" "	

HEXINT		0[xX][0-9a-fA-F]+
NUMINT		{DIGITS}|{HEXINT}

FLOAT_EXP_A	([eE][-+]?{DIGITS})?
FLOAT_A1	({DIGITS})?("."{DIGITS}){FLOAT_EXP_A}
FLOAT_A2	({DIGITS})("."{DIGITS}?)?{FLOAT_EXP_A}
FLOAT_A		{FLOAT_A1}|{FLOAT_A2}
FLOAT_EXP_B [pP][-+]?{DIGITS}
FLOAT_B1	0[xX]([0-9a-fA-F]*\.[0-9a-fA-F]+){FLOAT_EXP_B}
FLOAT_B2	0[xX]([0-9a-fA-F]+\.[0-9a-fA-F]*){FLOAT_EXP_B}
FLOAT_B3	0[xX]([0-9a-fA-F]+){FLOAT_EXP_B}
FLOAT_B		{FLOAT_B1}|{FLOAT_B2}|{FLOAT_B3}
FLOAT		{FLOAT_A}|{FLOAT_B}

%{
#include "lex.h"
#define _SHOW_WARNINGS 1

int LEX_LineNumber = 1;

static char* buffer_ptr;
static int buffer_pos = 0;
static int buffer_siz = 0;

seminfo_t LEX_seminfo;

// Reset Buffer
static void BUF_Reset(void) {
	buffer_pos = 0;
	buffer_ptr[buffer_pos] = '\0';
}

// Initialize the string buffer
static void BUF_Init(void) {
	if( buffer_siz == 0 ) {
		buffer_siz = 250;
		buffer_ptr = (char*)malloc(buffer_siz);
		buffer_ptr[0] = '\0';
		buffer_pos = 0;
	} else {
		BUF_Reset();
	}
}

static void BUF_Insert(char chr) {
	// If needed, expand the buffer size
	if ( buffer_pos == (buffer_siz-1) ) {
		buffer_siz += 50;
		buffer_ptr = (char*)realloc( buffer_ptr , buffer_siz );
	}
	// Add char to the buffer
	buffer_ptr[buffer_pos] = chr;
	buffer_pos++;
	buffer_ptr[buffer_pos] = '\0';
}

// Print the string buffer ( debug )
static void BUF_Print(void) {
	printf("\n\tBuffer: %s",buffer_ptr);
}

// Finalize string buffer
void BUF_Free(void) {
	if ( buffer_siz > 0 ) 
		free(buffer_ptr);
		buffer_siz = 0;
}

// Error message
static void LEX_error(const char* msg , const char* info ) {	
	fprintf(stderr, "\n\x1B[91mERROR: line %d: %s" , LEX_LineNumber , msg );
	
	if( info )
		fprintf(stderr, ": %s" , info );
		
	fprintf(stderr, "\x1B[0m\n" );
		
	BUF_Free();
	exit(1);
}

// Warning message
static void LEX_warning(const char* msg , const char* info ) {	
	#if _SHOW_WARNINGS == 0
		return;
	#endif

	fprintf(stderr, "\n\x1B[36mWARNING: line %d: %s" , LEX_LineNumber , msg );
	
	if( info )
		fprintf(stderr, ": %s" , info );
		
	fprintf(stderr, "\x1B[0m\n" );
}

%}



%x COMMENT STRING CHARCODE

%%
"/*"					{ BEGIN COMMENT; }
<COMMENT>"*/"			{ BEGIN 0; }
<COMMENT>\n				{ LEX_LineNumber++; }
<COMMENT><<EOF>> 		{ LEX_error("Comment not closed" , "end of file"); }
<COMMENT>.				{;}


{BLANK}+				{;}
\t	    				{;}
\n						{ LEX_LineNumber++; }


\"				{ BEGIN STRING; BUF_Init(); }
<STRING>\"		{ BEGIN 0; LEX_seminfo.s = buffer_ptr; return TK_STRING; }
<STRING>\n		{ LEX_LineNumber++; LEX_error("String not closed" , "new line before \""); }
<STRING><<EOF>> { LEX_error("String not closed" , "end of file"); }
<STRING>\\n		{ BUF_Insert('\n'); }
<STRING>\\t		{ BUF_Insert('\t'); }
<STRING>\t		{ BUF_Insert('\t'); }
<STRING>\\\"	{ BUF_Insert('"'); }
<STRING>\\\\	{ BUF_Insert('\\'); }
<STRING>\\.		{ LEX_error("Invalid escape" , yytext ); }
<STRING>.		{ BUF_Insert(yytext[0]); }


\'				{ BEGIN CHARCODE; BUF_Init(); }
<CHARCODE>\'	{ BEGIN 0; 
					LEX_seminfo.i = buffer_ptr[0];
					if ( buffer_pos > 1 )
						LEX_error("Invalid char simbol" , buffer_ptr );
					else
						return TK_NUM_CHAR; }
<CHARCODE>\\n	{ BUF_Insert('\n'); }
<CHARCODE>\\t	{ BUF_Insert('\t'); }
<CHARCODE>\t	{ BUF_Insert('\t'); }
<CHARCODE>\\\"	{ BUF_Insert('"'); }
<CHARCODE>\\\\	{ BUF_Insert('\\'); }	
<CHARCODE>\\.	{ LEX_error("Invalid escape" , yytext ); }
<CHARCODE>.		{ BUF_Insert(yytext[0]); }


"void"			{ return TK_VOID; }
"char"			{ return TK_CHAR; }
"int"			{ return TK_INT; }
"float"			{ return TK_FLOAT; }
"if"			{ return TK_IF; }
"else"			{ return TK_ELSE; }
"while"			{ return TK_WHILE; }
"new"			{ return TK_NEW; }
"return"		{ return TK_RETURN; }
">="			{ return TK_GE; }
"<="			{ return TK_LE; }
"=="			{ return TK_CE; }
"&&"			{ return TK_AND; }
"||"			{ return TK_OR; }


[)(}{;[\]!=+\-*/><] 		{ return yytext[0]; 
				  		//]
						}


{NUMINT}			{ LEX_seminfo.i = strtol( yytext , NULL , 0 ); return TK_NUM_INT; }
{FLOAT}				{ LEX_seminfo.f = strtof( yytext , NULL ); return TK_NUM_FLOAT; }
		

[a-zA-Z][a-zA-Z0-9_]*	{ LEX_seminfo.s = yytext; return TK_ID; }


.				{ // Other Tokens
				LEX_warning("Undefined token registered" , yytext );  
				return yytext[0];  }

%%
