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

int nodeCheck( ABS_node* node );
int nodeCheck_list( ABS_node* node );
int nodeCheck_declaration( ABS_node* node );
int nodeCheck_command( ABS_node* node );
int nodeCheck_var( ABS_node* node );
int nodeCheck_exp( ABS_node* node );
int nodeCheck_id( ABS_node* node );
int nodeCheck_funcCall( ABS_node* node );


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
		indexType = nodeCheck( node->node.var.index );
		//indexType = getArrayFinalType( indexType );
		
		if( indexType != INT ) {
			TOL_error("Index not an integer" , node->node.var.id->line , ""  );
		}
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
		
		if( parType != argType ) {
			TOL_error( "Invalid argument type" , node->line , tArg->node.decl.vardecl.id->node.id.name );
		} 
	
		tArg = tArg->next;
		tParam = tParam->next;
	}
	
	// Check param qtd vs arg art
	if( tArg != NULL ) {
		TOL_error( "Too many arguments" , node->line , tArg->node.decl.vardecl.id->node.id.name );
	} else if( tParam != NULL ) {
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
			type1 = nodeCheck( node->node.exp.data.newexp.exp );	
			if( type1 != INT ) {
				TOL_error("Size of new array not an integer" , node->line , ""  );
			}
			
			evalType = node->node.exp.data.newexp.type;	
			evalType += TYPEQTY;
			break;
			
		case EXP_BINOP:
			op = node->node.exp.data.operexp.opr;
			type1 = nodeCheck( node->node.exp.data.operexp.exp1 );
			type2 = nodeCheck( node->node.exp.data.operexp.exp2 );		
			
			// Check types
			if( type1 == INT && type2 == FLOAT ) {
				cast = ABS_addCastNode( node->node.exp.data.operexp.exp1 , FLOAT );
				node->node.exp.data.operexp.exp1 = cast;
				type3 = FLOAT;
			} else if ( type1 == FLOAT && type2 == INT ) {
				cast = ABS_addCastNode( node->node.exp.data.operexp.exp2 , FLOAT );
				node->node.exp.data.operexp.exp2 = cast;
				type3 = FLOAT;
			} else if ( type1 != type2 ) {
				TOL_typeError( "Incompatible types in binary operation" , node->line , type1 , type2 );
			} else {
				type3 = type1;
			}
			
			// Return the type of this expression
			switch( op ) {
				case '*':
				case '/':
				case '+':
				case '-':
					evalType = type3;
					break;
					
				default:
					evalType = INT;
					break;
			}
			break;
				
		case EXP_CALL:
			evalType = nodeCheck_funcCall( node );
			break;
			
		case EXP_VAR:
			evalType = nodeCheck_list( node->node.exp.data.varexp );
			break;
			
		case EXP_PAREN:
			evalType = nodeCheck_list( node->node.exp.data.parenexp );	
			break;
			
		case EXP_UNOP:
			op = node->node.exp.data.operexp.opr;
			type1 = nodeCheck_list( node->node.exp.data.operexp.exp1 );

			if( op == '-' ) {
				evalType = type1;
			} else {
				evalType = INT;
			}
		
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
			nodeCheck_list( node->node.cmd.ifcmd.exp );
			nodeCheck_list( node->node.cmd.ifcmd.cmd1 );
			nodeCheck_list( node->node.cmd.ifcmd.cmd2 );			
			return INT;
			
		case CMD_WHILE:
			nodeCheck_list( node->node.cmd.whilecmd.exp );
			nodeCheck_list( node->node.cmd.whilecmd.cmd  );
			return INT;
			
		case CMD_ATTR:
			type1 = nodeCheck( node->node.cmd.attrcmd.var );
			type2 = nodeCheck( node->node.cmd.attrcmd.exp );
			
			if( type1 == INT && type2 == FLOAT ) {
				TOL_error( "Cannot cast FLOAT to INT" , node->node.cmd.attrcmd.var->line , "" );
			} else if ( type1 == FLOAT && type2 == INT ) {
				cast = ABS_addCastNode( node->node.cmd.attrcmd.exp , FLOAT );
				node->node.cmd.attrcmd.exp = cast;
			} else if( type1 != type2 ) {
				TOL_typeError( "Incompatible types in attribution" , node->node.cmd.attrcmd.var->line , type1 , type2 );
			} 

			return INT;

		case CMD_EXP:
			return nodeCheck_list( node->node.cmd.expcmd.exp );
			
		case CMD_BLOCK:
			nodeCheck_list( node->node.cmd.blockcmd.decl );
			nodeCheck_list( node->node.cmd.blockcmd.cmd );
			return -1;
			
		case CMD_RET:
			type1 = nodeCheck_list( node->node.cmd.expcmd.exp );
			type2 = getIDType( node );
			
			if( type1 == INT && type2 == FLOAT ) {
				cast = ABS_addCastNode( node->node.cmd.expcmd.exp , FLOAT );
				node->node.cmd.expcmd.exp = cast;
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
