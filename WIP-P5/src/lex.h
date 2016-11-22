extern int yylex (void);

typedef union Seminfo_t {
	int i;
	double f;
	char *s;
} seminfo_t;
extern seminfo_t LEX_seminfo;

extern int LEX_LineNumber;

extern void BUF_Free(void);
