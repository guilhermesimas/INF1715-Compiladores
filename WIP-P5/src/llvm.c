void codeFuncDecl( nodeDecl* node ) {
	char* type = getType( node->funcdecl.type );
	char* func_name = node->funcdecl.id->node.id; //@func_name
	printf( "define %s @%s", type, func_name );
	codeParam( node->funcdecl.param );
	codeBlock( node->funcdecl.block->node.cmd );


}
/*
 * returns the corresponding llvm type (int = i32, for example)
 */
char* getType( int type ) {
	//TODO
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