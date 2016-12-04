#include "astKnit.h"
#include "types.h"
#include "absSyntaxTree.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ScopeTree scopeTree;


ABS_node* findID( char* id , ScopeLevel* tLevel , int* distance ) {
	ScopeNode*	tNode;
	
	int dist = 0;
	
	if( tLevel == NULL ) {
		tLevel = scopeTree.currentLevel;
	}
	
	tNode = tLevel->firstNode;
	for(;;) {
		while( tNode == NULL ) {
			// Find non empty upper scopes 
			dist++;
			
			tLevel = tLevel->upperLevel;
			if( tLevel == NULL ) { 
				return NULL;
			}
			
			tNode = tLevel->firstNode;
		}
	
	
		while( tNode != NULL ) {
			// Check if is found
			if( strcmp( tNode->id , id ) == 0 ) { 
				if( distance != NULL ) {
					(*distance) = dist;
				}
				return tNode->absNode;
			}
			
			// Prepare loop next step
			if( tNode == tLevel->lastNode ) {
				tNode = NULL;
			} else {
				tNode = tNode->next;
			}
		}
	}
}


void newScopeNode( ABS_node* absNode ) {
	ScopeNode* 	nNode;
	char*		id;
	int			existanceState;
	
	// Find Name
	if( absNode->tag == DEC_VAR ) {
		id = absNode->node.decl.vardecl.id->node.id.name;

		if( findID( id ,  NULL , &existanceState ) != NULL ) {
			if( existanceState == 0 ) {
				TOL_error("Variable already declared in this scope" , absNode->node.decl.vardecl.id->line , id );
			} else if( existanceState > 0 ) { 
				TOL_warning("Variable shadowing" , absNode->node.decl.vardecl.id->line , id );
			} 
		}
	} else {
		id = absNode->node.decl.funcdecl.id->node.id.name;
		
		if( findID( id ,  scopeTree.rootLevel , &existanceState ) != NULL ) {
			if( existanceState >= 0 ) {
				TOL_error("Function already declared" , absNode->node.decl.funcdecl.id->line , id );
			} 
		}
	}
	
	// Create node
	nNode = (ScopeNode*)malloc( sizeof(ScopeNode) );
	TOL_checkAlloc( nNode , "Falha ao alocar novo ScopeNode" , "" );
	
	nNode->next 		= NULL;
	nNode->absNode		= absNode;
	nNode->id			= id;	
	

	// Add to the tree
	if( scopeTree.currentLevel-> firstNode == NULL ) {
		scopeTree.currentLevel->firstNode = nNode;
	} else {
		scopeTree.currentLevel->lastNode->next = nNode;
	}
	
	scopeTree.currentLevel->lastNode = nNode;
}


void freeScopeNode( ScopeNode* sNode ) {
	free(sNode);
}


ScopeLevel* newScopeLevel(void) {
	ScopeLevel* nLevel = (ScopeLevel*)malloc( sizeof(ScopeLevel) );
	TOL_checkAlloc( nLevel , "Falha ao alocar novo ScopeLevel" , "" );	
	
	nLevel->firstNode = NULL;
	nLevel->lastNode = NULL;
	
	if( scopeTree.rootLevel == NULL ) {
		nLevel->upperLevel = NULL;
	} else {
		nLevel->upperLevel = scopeTree.currentLevel;
	}
	
	return nLevel;
}


void freeScopeLevel(ScopeLevel* sLevel ) {
	ScopeNode* cNode;
	ScopeNode* nNode;
		
	cNode = sLevel->firstNode;
	
	while( cNode != NULL ) {
		nNode = cNode->next;
		freeScopeNode(cNode);
		cNode = nNode;
	}
	
	free(sLevel);
}


void initScopeTree(void) {
	ScopeLevel* topLevel 	= newScopeLevel();
	scopeTree.rootLevel		= topLevel;
	scopeTree.currentLevel	= topLevel;	
}


void freeScopeTree(void) {
	ScopeLevel* sLevel = scopeTree.currentLevel;
	ScopeLevel* tLevel;
	
	while( sLevel != NULL ) {
		tLevel = sLevel->upperLevel;
		freeScopeLevel( sLevel );
		sLevel = tLevel;
	}
}

/*
 --- KNIT Algorithm ------------------------------------------------------------
*/
void enterScope(void);
void exitScope(void);
void nodeDive( ABS_node* node );
void nodeDive_list( ABS_node* node );
void nodeDive_declaration( ABS_node* node );
void nodeDive_command( ABS_node* node );
void nodeDive_var( ABS_node* node );
void nodeDive_exp( ABS_node* node );
void nodeDive_id( ABS_node* node );


void enterScope(void) {
	ScopeLevel* newLevel 		= newScopeLevel(); 
	scopeTree.currentLevel		= newLevel;	
}


void exitScope(void) {
	ScopeLevel* currentLevel 	= scopeTree.currentLevel;
	scopeTree.currentLevel		= currentLevel->upperLevel;
	freeScopeLevel( currentLevel );	
}


void nodeDive_list( ABS_node* node ) {
	while( node != NULL ) {
		nodeDive( node );
		node = node->next;
	}
}


void nodeDive_declaration( ABS_node* node ) { 
	newScopeNode( node );
	if( node->tag == DEC_FUNC ) {
		scopeTree.lastFunctionDeclaration = node;
		
		// Mark return
		if( node->node.decl.funcdecl.type == VOID ) {
			scopeTree.lastFuncReturned = 1;
		} else {
			scopeTree.lastFuncReturned = 0;
		}
		
		// Enter Scope and Knit
		enterScope();
		
		nodeDive_list( node->node.decl.funcdecl.param );

		nodeDive_list( node->node.decl.funcdecl.block->node.cmd.blockcmd.decl );
		nodeDive_list( node->node.decl.funcdecl.block->node.cmd.blockcmd.cmd );
	
		// Exit scope and clean
		exitScope();
		scopeTree.lastFunctionDeclaration = NULL;
		
		// Check return
		if( scopeTree.lastFuncReturned == 0 ) {
			TOL_error("Fuction without return" , node->line , node->node.decl.funcdecl.id->node.id.name  );
		}	
	}
}


void nodeDive_var( ABS_node* node ) { 
	nodeDive_list( node->node.var.id );
	nodeDive_list( node->node.var.index );
}


void nodeDive_id( ABS_node* node ) {
	ABS_node* 	matchingAbsNode;
	int existanceState;
	
	matchingAbsNode = findID( node->node.id.name ,  NULL , &existanceState );

	if ( matchingAbsNode == NULL ) {
		TOL_error("Invalid identifier" , node->line , node->node.id.name  );
	} else {
		node->declNode = matchingAbsNode;
		node->declDist = existanceState;
	}
}


void nodeDive_exp( ABS_node* node ) {		
	switch( node->tag ) {
		case EXP_NEW:	
			nodeDive_list( node->node.exp.data.newexp.exp );	
			break;
			
		case EXP_ARIT:
		case EXP_COMP:
		case EXP_ANDOR:
			nodeDive_list( node->node.exp.data.operexp.exp1 );
			nodeDive_list( node->node.exp.data.operexp.exp2 );		
			break;
				
		case EXP_CALL:
			nodeDive_list( node->node.exp.data.callexp.exp1 );
			nodeDive_list( node->node.exp.data.callexp.exp2 );	
			break;
			
		case EXP_VAR:
			nodeDive_list( node->node.exp.data.varexp );
			break;
			
		case EXP_UNOP:
		case EXP_NOT:
			nodeDive_list( node->node.exp.data.operexp.exp1 );
			break;
			
		case LIT_INT:
			break;
			
		case LIT_FLOAT:
			break;
			
		case LIT_STRING:	
			break;
			
	}
}


void nodeDive_command( ABS_node* node ) {
	switch( node->tag ) {	
		case CMD_IF:
			nodeDive_list( node->node.cmd.ifcmd.exp );
			nodeDive_list( node->node.cmd.ifcmd.cmd1 );
			nodeDive_list( node->node.cmd.ifcmd.cmd2 );			
			break;
			
		case CMD_WHILE:
			nodeDive_list( node->node.cmd.whilecmd.exp );
			nodeDive_list( node->node.cmd.whilecmd.cmd  );
			break;
			
		case CMD_ATTR:
			nodeDive_list( node->node.cmd.attrcmd.var );
			nodeDive_list( node->node.cmd.attrcmd.exp );
			break;

		case CMD_EXP:
			nodeDive_list( node->node.cmd.expcmd.exp );
			break;
			
		case CMD_BLOCK:
			enterScope();
			nodeDive_list( node->node.cmd.blockcmd.decl );
			nodeDive_list( node->node.cmd.blockcmd.cmd );
			exitScope();
			break;
			
		case CMD_RET:
			nodeDive_list( node->node.cmd.expcmd.exp );
			node->declNode = scopeTree.lastFunctionDeclaration;
			scopeTree.lastFuncReturned = 1;
			break;
	}
}


void nodeDive( ABS_node* node ) {
	switch( node->type ) {
		case TYPE_DECL:
			nodeDive_declaration( node );
			return;
				
		case TYPE_ID:
			nodeDive_id( node );
			return;
		
		case TYPE_EXP:
			nodeDive_exp( node );
			return;
			
		case TYPE_VAR:
			nodeDive_var( node );
			return;
			
		case TYPE_CMD:
			nodeDive_command( node );
			return;
			
		default:
			return;
	}
}



void knitABS(void) {
	
	ABS_node* thisNode = programNode;	
	
	initScopeTree();
	
	nodeDive_list( thisNode );	
	
	freeScopeTree();
	
	return;
}
