extern int yylex (void);

typedef enum lex_tk {
	TK_VOID		= 300,
	TK_CHAR,
	TK_INT,
	TK_FLOAT,
	TK_IF,
	TK_ELSE,
	TK_WHILE,
	TK_NEW,
	TK_RETURN,
	TK_GE,
	TK_LE,
	TK_CE,
	TK_NE,	
	TK_AND,
	TK_OR,
	TK_ID,
	TK_NUM_CHAR,
	TK_NUM_INT,
	TK_NUM_FLOAT,
	TK_STRING,
} LEX_TK;

typedef union Seminfo_t {
	int i;
	double f;
	char *s;
} seminfo_t;
extern seminfo_t LEX_seminfo;

extern int LEX_LineNumber;

extern void BUF_Free(void);
