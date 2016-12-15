#ifndef ASTKNIT_HEADER
#define ASTKNIT_HEADER

#include "types.h"
#include "absSyntaxTree.h"

typedef struct _scopeNode 	ScopeNode;
typedef struct _scopeLevel 	ScopeLevel;
typedef struct _scopeList 	ScopeLevelList;

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


struct _scopeList {
	ScopeLevel*		rootLevel;
	ScopeLevel*		currentLevel;	
	ABS_node* 		lastFunctionDeclaration;	
	int				lastFuncReturned;
};

extern ScopeLevelList scopeLevelList;

void knitABS(void);


#endif











