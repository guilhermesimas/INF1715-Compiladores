#include "typeCheck.h"

#include "types.h"
#include "absSyntaxTree.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int getIDType( ABS_node* node ) {
	int typ;
	
	node = node->declNode;

	if( node->tag == DEC_VAR ) {
		typ = node->node.decl.vardecl.type;
	} else if( node->tag == DEC_FUNC ) {
		typ = node->node.decl.funcdecl.type;
	} 
	
	return typ;
}


char* getDeclID( ABS_node* node ) {
	char* id;
	
	node = node->declNode;

	if( node->tag == DEC_VAR ) {
		id = node->node.decl.vardecl.id->node.id.name;
	} else if( node->tag == DEC_FUNC ) {
		id = node->node.decl.funcdecl.id->node.id.name;
	} 
	
	return id;
}


int getArrayFinalType( int overflowedType ) {
	int type = overflowedType;
	
	while( type >= TYPEQTY ) {
		type -= TYPEQTY;
	}
	
	return type;
}

/*
 --- CHECK Algorithm ------------------------------------------------------------
*/
int validateAritOperation( ABS_node* expNode );
int validateArrayIndex( ABS_node* indexNode );
int validateAttribution( int leftType , int rightType , ABS_node* rightNode );
int validateDecidable( int type );

int nodeCheck( ABS_node* node );
int nodeCheck_list( ABS_node* node );
int nodeCheck_declaration( ABS_node* node );
int nodeCheck_command( ABS_node* node );
int nodeCheck_var( ABS_node* node );
int nodeCheck_exp( ABS_node* node );
int nodeCheck_id( ABS_node* node );
int nodeCheck_funcCall( ABS_node* node );



int validateAritOperation( ABS_node* expNode ) {
	int leftType , rightType, expType;
	ABS_node* cast;
	
	leftType = nodeCheck( expNode->node.exp.data.operexp.exp1 );
	rightType = nodeCheck( expNode->node.exp.data.operexp.exp2 );		
	
	// Check types
	if( leftType == INT && rightType == FLOAT ) {
		ABS_addCastNode( expNode->node.exp.data.operexp.exp1 , FLOAT );
		expType = FLOAT;
	} else if ( leftType == FLOAT && rightType == INT ) {
		ABS_addCastNode( expNode->node.exp.data.operexp.exp2 , FLOAT );
		expType = FLOAT;
	} else if ( leftType != rightType ) {
		TOL_typeError( "Incompatible types in arithmetic operation" , expNode->line , leftType , rightType );
	} else {
		expType = leftType;
	}	
	
	return expType;
}


int validateArrayIndex( ABS_node* indexNode ) {
	int type; 
	
	type = nodeCheck( indexNode );	
	if( type != INT ) {
		TOL_error("Size of new array not an integer" , indexNode->line , ""  );
	}
}


int validateAttribution( int leftType , int rightType , ABS_node* rightNode ) {
	ABS_node* 	castNode;
	
	// Check types
	if ( leftType == FLOAT && rightType == INT ) {
		printf("\n\tATTR CAST\n");
		ABS_addCastNode( rightNode , FLOAT );
	}		
	else if( leftType == INT && rightType == FLOAT ) {
		TOL_typeError( "Incompatible types attribution" , rightNode->line , leftType , rightType );
	}
	else if ( leftType != rightType ) {
		TOL_typeError( "Incompatible types attribution" , rightNode->line , leftType , rightType );
	}	
	
	return leftType;
}


int validateDecidable( int type ) {
	if( type == VOID ) {
		return 0;
	} else {
		return 1;
	}
}

// ------------------------------------------------

int nodeCheck_list( ABS_node* node ) {
	int typ = -1;
	
	while( node != NULL ) {
		typ = nodeCheck( node );
		node = node->next;
	}
	
	return typ;
}


int nodeCheck_declaration( ABS_node* node ) { 
	if( node->tag == DEC_FUNC ) {
		return nodeCheck_list( node->node.decl.funcdecl.block->node.cmd.blockcmd.cmd );
	}
	
	return -1;
}


int nodeCheck_var( ABS_node* node ) { 
	int indexType;
	int typ;
	
	if( node->tag == VAR_ARRAY ) {
		validateArrayIndex( node->node.var.index );
	}

	typ = nodeCheck( node->node.var.id );

	// Step down array type	
	if( node->tag == VAR_ARRAY ) {
		typ = typ - TYPEQTY;
		
		if( typ < 0 ) {
			TOL_error("Too many indexation levels" , node->node.var.id->line , "" );
		}
	}
	
	node->node.var.type = typ;
	return typ;
}


int nodeCheck_id( ABS_node* node ) {
	return getIDType(node);
}


int nodeCheck_funcCall( ABS_node* node ) {
	ABS_node* declNode;
	ABS_node* tParam;
	ABS_node* tArg;	
	int parType , argType;
	
	// Check parameters vs argument types
	tArg = node->node.exp.data.callexp.exp2;
	tParam = node->node.exp.data.callexp.exp1;
	tParam = tParam->declNode->node.decl.funcdecl.param;

	while( tArg != NULL && tParam != NULL ) {
		argType = nodeCheck( tArg );
		parType = tParam->node.decl.vardecl.type;

		validateAttribution( parType , argType , tArg );	

		tArg = tArg->next;
		tParam = tParam->next;
	}
	
	// Check param qtd vs arg qtd
	if( tArg != NULL ) {
		TOL_error( "Too many arguments" , node->line , tArg->node.decl.vardecl.id->node.id.name );
	}
	else if( tParam != NULL ) {
		TOL_error( "Missing argument" , node->line , tParam->node.decl.vardecl.id->node.id.name );
	}
	
	return nodeCheck(node->node.exp.data.callexp.exp1);
} 




int nodeCheck_exp( ABS_node* node ) {	
	int type1 , type2 , type3 , op;
	int evalType;
	ABS_node* cast;
	
	switch( node->tag ) {
		case EXP_NEW:	
			validateArrayIndex( node->node.exp.data.newexp.exp );
			evalType = node->node.exp.data.newexp.type;	
			evalType += TYPEQTY;
			break;
			
			
		case EXP_ARIT:
			evalType = validateAritOperation( node );
			break;
			
					
		case EXP_COMP:
			validateAritOperation( node );
			evalType = INT;
			break;	
					
		
		case EXP_ANDOR:				
			//op = node->node.exp.data.operexp.opr;
			type1 = nodeCheck( node->node.exp.data.operexp.exp1 );
			type2 = nodeCheck( node->node.exp.data.operexp.exp2 );	
			
			if( !validateDecidable( type1 ) || !validateDecidable( type2 ) ) {	
				TOL_error( "Operators not decidable" , node->line , "" );			
			} 		
			
			evalType = INT;
			break;	
			
				
		case EXP_CALL:
			evalType = nodeCheck_funcCall( node );
			break;
			
			
		case EXP_VAR:
			evalType = nodeCheck( node->node.exp.data.varexp );
			break;
			
		
		case EXP_NOT:
			nodeCheck( node->node.exp.data.operexp.exp1 );
			evalType = INT;
			break;		
		
			
		case EXP_UNOP:
			evalType = nodeCheck( node->node.exp.data.operexp.exp1 );
			break;
			
			
		case LIT_INT:
			evalType = INT;
			break;
			
			
		case LIT_FLOAT:
			evalType = FLOAT;
			break;
		
			
		case LIT_STRING:
			evalType = STRING;	
			break;
	}
	
	node->node.exp.type = evalType;
	return evalType;	
}


int nodeCheck_command( ABS_node* node ) {
	int type1 , type2 , type3 , op;
	ABS_node* cast;

	switch( node->tag ) {	
		case CMD_IF:
			type1 = nodeCheck( node->node.cmd.ifcmd.exp );
			
			if( !validateDecidable( type1 ) ) {
				TOL_error( "If condition not decidable" , node->line , "" );
			}			
			
			nodeCheck_list( node->node.cmd.ifcmd.cmd1 );
			nodeCheck_list( node->node.cmd.ifcmd.cmd2 );			
			return INT;
			
		case CMD_WHILE:
			type1 = nodeCheck( node->node.cmd.whilecmd.exp );
			
			if( !validateDecidable( type1 ) ) {
				TOL_error( "While condition not decidable" , node->line , "" );
			}
	
			nodeCheck_list( node->node.cmd.whilecmd.cmd  );
			return INT;
			
		case CMD_ATTR:
			type1 = nodeCheck( node->node.cmd.attrcmd.var );
			type2 = nodeCheck( node->node.cmd.attrcmd.exp );		
			validateAttribution( type1 , type2 , node->node.cmd.attrcmd.exp);		
			return INT;

		case CMD_EXP:
			return nodeCheck( node->node.cmd.expcmd.exp );
			
		case CMD_BLOCK:
			nodeCheck_list( node->node.cmd.blockcmd.decl );
			nodeCheck_list( node->node.cmd.blockcmd.cmd );
			return -1;
			
		case CMD_RET:
			type1 = nodeCheck( node->node.cmd.retcmd.exp );
			type2 = getIDType( node );
			
			node->node.cmd.retcmd.type = type2;

			if( type1 == INT && type2 == FLOAT ) {
				ABS_addCastNode( node->node.cmd.expcmd.exp , FLOAT );
			} else if( type1 != type2 ) {
				TOL_error( "Function returning wrong type" , node->line , node->declNode->node.decl.funcdecl.id->node.id.name );
			}			
			return INT;
	}
}


int nodeCheck( ABS_node* node ) {
	switch( node->type ) {	
		case TYPE_DECL:
			return nodeCheck_declaration( node );
					
		case TYPE_ID:
			return nodeCheck_id( node );
		
		case TYPE_EXP:
			return nodeCheck_exp( node );
			
		case TYPE_VAR:
			return nodeCheck_var( node );
			
		case TYPE_CMD:
			return nodeCheck_command( node );
			
		default:
			return -1;
	}
}



void typeCheckABS(void) {
	ABS_node* thisNode = programNode;	
	
	nodeCheck_list( thisNode );	
	
	return;
}
