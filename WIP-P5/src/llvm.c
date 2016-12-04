#include "llvm.h"
#include "types.h"
#include "absSyntaxTree.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int g_ident = 0; // Current identation level
static int g_vid = 0; // Next FREE var id
static int g_lid = 0; // Next FREE label id
static int g_lastOpenLabel = -1; // Last opened label ID


/*
 * returns the corresponding llvm type (int = i32, for example)
 */
char* codeAux_getType( int type ) {
	switch ( type ) {
	case INT: {
		return "i32";
		break;
	}
		//TODO: other cases

	}
}
/*
 * returns the corresponding llvm size (int = 4, for example)
 */
int codeAux_getSize( int type ) {
	switch ( type ) {
	case INT: {
		return 4;
		break;
	}
		//TODO: other cases

	}
}

// FLUFF: Keep Track of identation
void codeAux_enterBlock(void) {
	g_ident++;
}

// FLUFF: Keep Track of identation
void codeAux_exitBlock(void) {
	g_ident--;
}

// FLUFF: Print Current identation ( with new line )
void code_printIdent(void) {
	int i;
	printf("\n");
	for( i = 0 ; i < g_ident ; i++ ) {
		printf("  ");
	}
}

// Control: reset function bound globals
void codeAux_resetFuncGlobals(void) {
	g_vid = 0;
	g_lid = 0;
	g_lastOpenLabel = -1;
}

// ---------------------------------------------------------------------------------------------------

// Link with AST: Set node last tracked ID on LLVM ( mainly or declarations and atributions )
void link_setLastID( ABS_node* node ) {
	switch( node->tag ) {
		case DEC_VAR:
			node->node.decl.vardecl.lastCodeID = g_vid;
			break;
	}
}

// Link with AST: Get node last tracked ID on LLVM ( mainly for variables )
int link_getLastID( ABS_node* node ) {
	switch( node->tag ) {
		case DEC_VAR:
			return node->node.decl.vardecl.lastCodeID;
			
		case VAR_MONO:
			return link_getLastID(node->node.var.id->declNode);
			
		case EXP_VAR:								
			return link_getLastID(node->node.exp.data.varexp);
	}
}

// Print a literal node preceeded of its type code
void code_literalNode( ABS_node* node ) {
	char* type = codeAux_getType( node->node.exp.type );
	
	switch( node->tag ) {
		case LIT_INT:
			printf("%s %d" , type , node->node.exp.data.literal.vInt );
			break;	
			
		case LIT_FLOAT:
			printf("FLOAT");
			break;	
			
		case LIT_STRING:
			printf("STRING");
			break;	
	}	
}

// Print a id on llvm format, simple but grants name prefix
void code_llvmID( int id ) {
	printf("%%v_%d", id);
}

// Create a new var ( updateglobal id ) and print its reference
int code_newVar(void) {
	int id = g_vid;
	g_vid++;
	code_llvmID( id );
	return id;
}

// Generate code for: alloca and return its ID
int code_alloca( int aType ) {
	int id;
	char* type;
	int size;
	
	type = codeAux_getType( aType );
	size = codeAux_getSize( aType );

	// Alloca
	code_printIdent();
	id = code_newVar();	
	printf(" = alloca %s, align %d" , type , size );
	
	return id;
}


// Generate code for: store of literal onto sId
void code_storeLiteralInt( int sType , int sId , ABS_node* literal ) {
	char* type;
	int size;
	
	type = codeAux_getType( sType );
	size = codeAux_getSize( sType );

	// Store
	code_printIdent();
	printf("store " );
	code_literalNode( literal );
	printf(", %s* ", type );
	code_llvmID( sId );
	printf(", align %d" , size );
}

// Generate code for: load and lId of lType and return its new ID
int code_load( int lType , int lId  ) {
	int id;
	char* type;
	int size;
	
	type = codeAux_getType( lType );
	size = codeAux_getSize( lType );	
	code_printIdent();
	id = code_newVar();	
	printf(" = load %s, %s* " , type , type );
	code_llvmID( lId );	
	printf(", align %d",size);
			
	return id;
}


// Generate code for: jump to lid
void code_jumpLabel( int lid ) {
	code_printIdent();	
	printf("br label %%l_%d", lid );
}


// Generate code for: end current label with: a jump to lid if lid >= 0
// Only needed to end a label early, with a jump that is not to the next label
void code_endLabel( int lid ) {
	g_lastOpenLabel = -1;
	
	if( g_lid >= 0 ) { 
		code_jumpLabel( lid );
	}
}


// Generate code for: open a new label, returns the ID of the new label
int code_startLabel(void) {
	int labelID;

	// new id control
	labelID = g_lid;
	g_lid++;
	
	// If theres an opened label, finish it with a jump for this new label
	if( g_lastOpenLabel >= 0 ) {
		code_endLabel( labelID );
	}
	
	// last id control
	g_lastOpenLabel = labelID;	

	// Visual fluff
	printf("\n");
	code_printIdent();	
	
	// Label print
	printf("l_%d:", labelID );
	
	return labelID;
}

// --------------------------------------------------------------------
// Main Code
// --------------------------------------------------------------------

void genCode_list( ABS_node* node );
void genCode( ABS_node* node );
void codeDecl( ABS_node* node );
void codeDeclFunc( ABS_node* node );
void codeDeclVar( ABS_node* node );
void codeParam( ABS_node* param );
void codeFuncBody( ABS_node* block );
void codeVarDecl( ABS_node* decl );
void codeCmd( ABS_node* cmd );
int codeExp( ABS_node* exp );
void codeCmd_ret( ABS_node* cmd );
int codeCmd_atr( ABS_node* cmd );


void genASTCode(void) {
	ABS_node* thisNode = programNode;	
	
	genCode_list( thisNode );	
}


void genCode_list( ABS_node* node ) {

	while( node != NULL ) {
		genCode( node );
		node = node->next;
	}
}


void genCode(ABS_node* node) {
	switch( node->type ) {	
		case TYPE_DECL:
			return codeDecl( node );
					
		case TYPE_ID:
			//return genCode_id( node );
		
		case TYPE_EXP:
			//return genCode_exp( node );
			
		case TYPE_VAR:
			//return genCode_var( node );
			
		case TYPE_CMD:
			return codeCmd( node );
			
		default:
			return;
	}
}


/*
 * generates code for declarations
 */

void codeDecl( ABS_node* node ) {
	switch ( node->tag ) {
		case DEC_FUNC: {
			codeDeclFunc( node );
			break;
		}
		case DEC_VAR: {
			codeDeclVar( node );
			break;
		}
	}
}


/*
 * generates code for variable definition
 */
void codeDeclVar( ABS_node* node ) {
	//%name = alloca <type>, align <size>

	char* name = node->node.decl.vardecl.id->node.id.name;
	char* type = codeAux_getType( node->node.decl.vardecl.type );
	int size = codeAux_getSize( node->node.decl.vardecl.type );
	
	code_printIdent();	
	code_llvmID(g_vid);
	printf( " = alloca %s,align %d", type, size );
	link_setLastID( node );
	g_vid++;
}


/*
 * generates code for function definiton
 */
void codeDeclFunc( ABS_node* node ) {
	char* type = codeAux_getType( node->node.decl.funcdecl.type );
	char* func_name = node->node.decl.funcdecl.id->node.id.name; //@func_name
				
	codeAux_resetFuncGlobals();			
				
	printf("\ndefine %s @%s", type, func_name );

	codeParam( node->node.decl.funcdecl.param );
	codeFuncBody( node->node.decl.funcdecl.block );
}


/*
 * prints the parameters in the llvm format
 */
void codeParam( ABS_node* param ) {
	char* type;
	char* id;
	ABS_node* current;
	int  commaFlag = 0;
	
	printf( "( " );
	
	while( param != NULL ) {
		//id = param->node.decl.vardecl.id->node.id.name;
		type = codeAux_getType( param->node.decl.vardecl.type );
		
		// Annoying Separator Flag
		if( commaFlag ) {
			printf(" , ");
		}
		else {
			commaFlag = 1;
		}
		
		// Var ID and Type
		printf( "%s ", type );
		code_llvmID(g_vid);
		link_setLastID( param );
		g_vid++;
		
		param = param->next;
	}

	printf( " )" );
	
	// Start of function block
	// WIP: LLVM auto generated code realloc arguments at start of the function block. 
	// Hovewer, up until now the code worked without it
	
	code_printIdent();
	printf( "{" );
	codeAux_enterBlock();
}


/*
 * generates code for the body of the function
 */

void codeFuncBody( ABS_node* block ) {
	genCode_list( block->node.cmd.blockcmd.decl );
	genCode_list( block->node.cmd.blockcmd.cmd );	

	codeAux_exitBlock();
	
	code_printIdent();
	printf( "}\n" );
}


/*
 * generates code for a block
 */

void codeBlock( ABS_node* block ) {
	code_printIdent();
	printf( "{" );
	
	codeAux_enterBlock();

	genCode_list( block->node.cmd.blockcmd.decl );
	genCode_list( block->node.cmd.blockcmd.cmd );	

	codeAux_exitBlock();
	
	code_printIdent();
	printf( "}\n" );
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
void codeCmd( ABS_node* cmd ) {
	switch ( cmd->tag ) {
		case CMD_RET: {
			codeCmd_ret( cmd );
			break;
		}
			
		case CMD_ATTR: {
			codeCmd_atr( cmd );	
			break;
		}
			//TODO: other cases
	}
	//cmd->node.cmd.retcmd : struct(ABS_node* exp)
}

/*
 * generates code for exp
 */

int codeExp( ABS_node* exp ) {
	int id;
	int size;
	char* type;
	
	switch ( exp->tag ) {
		case EXP_VAR: {
			id = link_getLastID(exp);
			break;
		}
	
		case EXP_ARIT: {
			int id1 , id2;
			type = codeAux_getType( exp->node.exp.type );
			
			id1 = codeExp( exp->node.exp.data.operexp.exp1 );
			id2 = codeExp( exp->node.exp.data.operexp.exp2 );

			// Assigment Part
			code_printIdent();			
			id = code_newVar();
			printf(" = ");
			
			// Signal Part
			switch( exp->node.exp.data.operexp.opr ) {
				case '+':
					printf("add");
					break;
				
				case '-':
					printf("sub");
					break;
					
				case '*':
					printf("mul");
					break;				
				
				case '/':
					printf("sdiv");
					break;	
			}
			
			// References Part
			printf(" nsw %s " , type );
			code_llvmID(id1);
			printf(" , ");
			code_llvmID(id2);			
			
			break;
		}
	
		case LIT_INT: {
			int id2;
		
			type = codeAux_getType( INT );
			size = codeAux_getSize( INT );
		
			// Alloca
			id2 = code_alloca( INT );
			
			// Store
			code_storeLiteralInt( INT , id2 , exp );
			
			// Load
			id = code_load( INT , id2  );
			
			break;
		}
			//TODO: other cases
	}
	
	return id;
}


/*
 * generates code for return
 */
void codeCmd_ret( ABS_node* cmd ) {
	char* type = codeAux_getType( cmd->node.cmd.retcmd.type );
	
	switch( cmd->node.cmd.retcmd.exp->tag ) {
		case LIT_INT:
		case LIT_FLOAT:
		case LIT_STRING:
			code_printIdent();
			printf("ret " );		
			code_literalNode( cmd->node.cmd.retcmd.exp );
			break;	
			
		default:
			{
			int id = codeExp( cmd->node.cmd.retcmd.exp );
			code_printIdent();
			printf("ret %s " , type );	
			code_llvmID(id);
			}
	}		

}


/*
 * generates code for attribution
 */
int codeCmd_atr( ABS_node* cmd ) {
	int id;

	// TODO: everything

	return id;
}

