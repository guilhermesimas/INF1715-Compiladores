#ifndef ASTKNIT_HEADER
#define ASTKNIT_HEADER

#include "types.h"
#include "absSyntaxTree.h"

typedef struct _scopeNode 	ScopeNode;
typedef struct _scopeLevel 	ScopeLevel;
typedef struct _scopeTree 	ScopeTree;

struct _scopeNode {
    ScopeNode* 		next;
    ABS_node* 		absNode;
    char*			id;          
};


struct _scopeLevel {
	ScopeNode*		firstNode;
	ScopeNode*		lastNode;
	ScopeLevel*		upperLevel;
};


struct _scopeTree {
	ScopeLevel*		rootLevel;
	ScopeLevel*		currentLevel;	
	ABS_node* 		lastFunctionDeclaration;	
	int				lastFuncReturned;
};

extern ScopeTree scopeTree;

void knitABS(void);


#endif











