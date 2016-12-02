#include "llvm.h"

void genCode() {
	for ( ABS_node* n = programNode; n != NULL; n = n->next ) {
		codeDecl( n );
		printf( "\n" );
	}
}

/*
 * generates code for a definition (or declaration?)
 */

void codeDecl( ABS_node* node ) {
	switch ( node->tag ) {
	case DEC_FUNC: {
		codeDeclFunc( &( node->decl ) );
		break;
	}
	case DEC_VAR: {
		codeDeclVar( &( node->decl ) );
		break;
	}
	}
}

/*
 * generates code for function definiton
 */

void codeDeclFunc( nodeDecl* node ) {
	char* type = getType( node->funcdecl.type );
	char* func_name = node->funcdecl.id->node.id; //@func_name
	printf( "define %s @%s", type, func_name );
	codeParam( node->funcdecl.param );
	codeBlock( node->funcdecl.block->node.cmd );


}
/*
 * generates code for variable definition
 */
void codeDeclVar( nodeDecl* node ) {
	//WIP

}
/*
 * returns the corresponding llvm type (int = i32, for example)
 */
char* getType( int type ) {
	switch ( type ) {
	case INT: {
		return "i32";
		break;
	}
		//TODO: other cases

	}
}
/*
 * prints the parameters in the llvm format
 */
void codeParam( ABS_node* param ) {
	ABS_node* current;
	printf( "(" );
	if ( param != NULL ) {
		char* type = getType( n.type );
		char* id = node->id;
		printf( "%s %%%s", type, node->id ); //prints first param
		for ( ABS_node* n = param->next; n != NULL ; n = n->next ) {
			char* type = getType( n.type );
			char* id = node->id;
			printf( ",%s %%%s", type, node->id );//prints next param
		}
	}
	printf( ")" );
}
/*
 * prints a block
 */

void codeBlock( ABS_nodeCMD* block ) {
	printf( "{" );
	//block->blockcmd:struct(decl:node*,cmd:node*)
	codeVarDecl( block->blockcmd.decl );
	codeCmd( block->blockcmd.cmd );

	printf( "}" );
}

/*
 * generates code for variable declarations (alloca)
 */

void codeVarDecl( ABS_node* decl ) {
	//TODO
}

/*
 * generates code for commands
 */
void codeCmd( ABS_node*cmd ) {
	switch ( cmd->tag ) {
	case CMD_RET: {
		printf( "ret " );
		codeExp();
		break;
	}
		//TODO: other cases
	}
	//cmd->node.cmd.retcmd : struct(ABS_node* exp)
}

/*
 * generates code for exp
 */

void codeExp( ABS_node* exp ) {
	switch ( exp->tag ) {
	case LIT_INT: {
		printf( "i32 %d ", exp->node.exp.literal.vInt );
		break;
	}
		//TODO: other cases
	}
}