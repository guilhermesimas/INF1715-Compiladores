#include "llvm.h"
#include "types.h"
#include "absSyntaxTree.h"
#include "tools.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VAR_ARRAY_SIZE 10
#define VAR_NOT_INITIALIZED -1

static int g_ident = 0; // Current identation level
static int g_vid = 0; // Next FREE LLVM var id
static int g_lid = 0; // Next FREE LLVM label id
static int g_lastOpenLabel = -1; // Last opened label ID

static int g_typeTracking[VAR_ARRAY_SIZE]; // Tracking of Index Types
static int g_nextVarRefIndex = 0; // Next FREE Tracking Reference Index
static int g_lastGlobalIndex = -1; // Last Tracking Index used by a Global Variable
static int g_globalScope = 0;


/*
 * returns the corresponding llvm type (int = i32, for example)
 */
char* codeAux_getType( int type ) {
	switch ( type ) {
	case INT: {
		return "i32";
		break;
	}

	case FLOAT: {
		return "float";
		break;
	}

	default:
		return "UNKNOWN";
		break;
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

	case FLOAT: {
		return 4;
		break;
	}
		//TODO: other cases

	}
}

/*
 * check if a EXP node is EXP-LITERAL
 */
int codeAux_isExpLiteral( ABS_node* node ) {
	switch ( node->tag ) {
	case LIT_INT:
	case LIT_FLOAT:
	case LIT_STRING:
		return 1;
		break;
	}

	return 0;
}

// FLUFF: Keep Track of identation
void codeAux_enterBlock( void ) {
	g_ident++;
}

// FLUFF: Keep Track of identation
void codeAux_exitBlock( void ) {
	g_ident--;
}


// Return the next free VID
int codeAux_newVid( void ) {
	int id = g_vid;
	g_vid++;
	return id;
}


// Copy Variable Tracking Array
void codeAux_copyTrackingArray( int* arrayTo , int* arrayFrom ) {
	int i;

	for ( i = 0 ; i < VAR_ARRAY_SIZE ; i++ ) {
		arrayTo[i] = arrayFrom[i];
	}
}


// Control: reset function LLVM_ID and LABEL globals
void codeAux_resetFuncGlobals( void ) {
	// LLVM temporary and label ids control
	g_vid = g_lastGlobalIndex + 1;
	g_lid = 0;
	g_lastOpenLabel = -1;
}


// Control: Prepare the system exit the global scope
// Set g_lastGlobalIndex
// Clear varTracking array ( if not null )
void codeAux_exitGlobalScope( int* varTracking ) {
	int i = 0;

	// Set the last global tracking index
	g_lastGlobalIndex = g_nextVarRefIndex - 1;

	// Reset all local variables to not initialized
	if ( varTracking != NULL ) {
		for ( i = g_nextVarRefIndex ; i < VAR_ARRAY_SIZE ; i++ ) {
			varTracking[i] = VAR_NOT_INITIALIZED;
		}
	}

	// Set Global Scope Flag
	g_globalScope = 0;
}


// Control: Prepare the system enter/return to the global scope
// Set g_nextVarRefIndex
void codeAux_enterGlobalScope( void ) {
	// Free Non Global Tracking Index Slots
	g_nextVarRefIndex = g_lastGlobalIndex + 1;

	// Set Global Scope Flag
	g_globalScope = 1;
}


// Generate new labelID
int codeAux_getNewLabel( void ) {
	int lid = g_lid;
	g_lid++;
	return lid;
}

// FLUFF: Get node name ( call , variable , function , declaration )
const char* codeAux_getNodeName( ABS_node* node ) {
	switch ( node->tag ) {
	case EXP_VAR:
		return codeAux_getNodeName( node->node.exp.data.varexp );

	case VAR_MONO:
	case VAR_ARRAY:
		return codeAux_getNodeName( node->node.var.id );

	case DEC_VAR:
		return codeAux_getNodeName( node->node.decl.vardecl.id );

	case DEC_FUNC:
		return codeAux_getNodeName( node->node.decl.funcdecl.id );

	case EXP_CALL:
		return codeAux_getNodeName( node->node.exp.data.callexp.exp1 );

	case ID:
		return node->node.id.name;

	}
}

// ---------------------------------------------------------------------------------------------------
void debug_printTrackingArray( int* varTracking ) {
	int i;
	for ( i = 0 ; i < VAR_ARRAY_SIZE ; i++ ) {
		printf( "\n\t: %d : %d " , i , varTracking[i] );
	}
}

// ---------------------------------------------------------------------------------------------------


// Link with AST: Set node tracked INDEX on LLVM Var Array ( mainly for declarations )
// Return: Track Index Generated
int track_setVarRef( ABS_node* node ) {
	switch ( node->tag ) {
	case DEC_VAR:
		// Var Tracker Index
		node->node.decl.vardecl.lastCodeID = g_nextVarRefIndex;

		// Var Tracker Type
		g_typeTracking[g_nextVarRefIndex] = node->node.decl.vardecl.type;

		// Control
		g_nextVarRefIndex++;
		return node->node.decl.vardecl.lastCodeID;

	case VAR_MONO:
		return track_setVarRef( node->node.var.id->declNode );

	case EXP_VAR:
		return track_setVarRef( node->node.exp.data.varexp );
	}
}

// Link with AST: Get node tracked INDEX on LLVM Var Array ( mainly for variables )
int track_getVarRef( ABS_node* node ) {
	switch ( node->tag ) {
	case DEC_VAR:
		return node->node.decl.vardecl.lastCodeID;

	case VAR_MONO:
		return track_getVarRef( node->node.var.id->declNode );

	case EXP_VAR:
		return track_getVarRef( node->node.exp.data.varexp );
	}
}

// Link with AST: Set the ID of NODE in VARTRACKING array to the NEWID
void track_setVarId( ABS_node* node , int* varTracking , int newId ) {
	int refId = track_getVarRef( node );
	varTracking[refId] = newId;
}

// Link with AST: Get the ID of NODE in VARTRACKING array
int track_getVarId( ABS_node* node , int* varTracking ) {
	int refId = track_getVarRef( node );
	return varTracking[refId];
}


// FLUFF: Print Current identation ( with new line )
void code_printIdent( void ) {
	int i;
	printf( "\n" );
	for ( i = 0 ; i < g_ident ; i++ ) {
		printf( "  " );
	}
}

// FLUFF: Print MSG with current identation ( with new line )
void code_printIdented( const char* msg ) {
	code_printIdent();

	printf( "%s", msg );
}

// Code for: LLVM Arith Operation
// LLVM Artih: <id> = { THIS CODE } id1 , id2
void code_ArithmeticType( int resultType , int operation ) {
	char* 	type;

	// Signal to llvm cmd part
	switch ( resultType ) {
	case FLOAT:
		printf( "f" );
		break;
	}

	switch ( operation ) {
	case '+':
		printf( "add" );
		break;

	case '-':
		printf( "sub" );
		break;

	case '*':
		printf( "mul" );
		break;

	case '/':
		if ( resultType == INT ) {
			printf( "sdiv" );
		} else {
			printf( "div" );
		}
		break;
	}

	// Complements
	if ( resultType == INT ) {
		printf( " nsw " );
	} else {
		printf( " " );
	}

	// Operation type
	type = codeAux_getType( resultType );
	printf( "%s " , type );
}

// Print an id on chosen LLVM variable name format
void code_llvmID_name( int id ) {
	printf( "v_%d", id );
}


// Print an id on llvm temporary_var format
void code_llvmID_LOC( int id ) {
	printf( "%%" );
	code_llvmID_name( id );
}


// Print an id on llvm global format
void code_llvmID_GLB( int id ) {
	printf( "@" );
	code_llvmID_name( id );
}


// Print an id on llvm format from a Tracker Index
// Decides if will be printed as global or temporary
void code_llvmID_IDX( int idx , int* varTracking ) {
	int id = varTracking[idx];

	if ( idx <= g_lastGlobalIndex ) {
		code_llvmID_GLB( id );
	}
	else {
		code_llvmID_LOC( id );
	}
}

// Print an id of an exp on llvm format, simple but grants name prefix
void code_nodeRepresentation( ABS_node* node , int id ) {
	switch ( node->tag ) {
	case LIT_INT:
		printf( "%d" , node->node.exp.data.literal.vInt );
		break;

	case LIT_FLOAT:
		printf( "%f" , node->node.exp.data.literal.vFloat );
		break;

	case LIT_STRING:
		// TODO
		break;

	default:
		code_llvmID_LOC( id );
		break;
	}
}

// Print LLVM format type
void code_type( int type ) {
	char* ctype = codeAux_getType( type );
	printf( "%s", ctype );
}

// Print LLVM format type of a node
void code_nodeType( ABS_node* node  ) {
	int type;

	switch ( node->type ) {
	case TYPE_EXP:
		type = node->node.exp.type;
		break;

	case TYPE_VAR:
		type = node->node.var.type;
		break;
	}

	code_type( type );
}


// Create a new var ( updateglobal id ) and print its reference
int code_newVar( void ) {
	int id = codeAux_newVid();
	code_llvmID_LOC( id );
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
	printf( " = alloca %s, align %d" , type , size );

	return id;
}


// Generate code for: store oId of sType into dId
void code_store( int oId , int dIndex , int* varTracking ) {
	char* type;
	int size;
	int sType;

	// Store Info
	sType = g_typeTracking[dIndex];
	type = codeAux_getType( sType );
	size = codeAux_getSize( sType );

	// Store
	code_printIdent();
	printf( "store %s " , type );
	code_llvmID_LOC( oId );
	printf( ", %s* ", type );
	code_llvmID_IDX( dIndex , varTracking );
	printf( ", align %d" , size );
}

// Generate code for: store of literal onto sId
void code_storeLiteral( int sId , ABS_node* literal ) {
	int type;
	int size;

	type = literal->node.exp.type;

	size = codeAux_getSize( type );

	// Store
	code_printIdent();
	printf( "store " );
	code_nodeType( literal );
	printf( " " );
	code_nodeRepresentation( literal , -1 );
	printf( ", " );
	code_type( type );
	printf( "* " );
	code_llvmID_LOC( sId );
	printf( ", align %d" , size );
}

// Generate code for: Load: load INDEX of 
// Return: loaded Local Var ID
int code_load( int index  , int* varTracking  ) {
	int id;
	int iType;
	char* type;
	int size;

	// Variable Info
	iType = g_typeTracking[index];
	type = codeAux_getType( iType );
	size = codeAux_getSize( iType );
	
	// LLVM code
	code_printIdent();
	id = code_newVar();
	printf( " = load %s, %s* " , type , type );
	code_llvmID_IDX( index , varTracking );
	printf( ", align %d", size );

	return id;
}


// Print an label id on llvm format, simple but grants prefix
void code_llvmLabel( int lid ) {
	printf( "%%l_%d", lid );
}

// Generate code for: label start
void code_label( int lid ) {
	// Visual fluff
	printf( "\n" );
	code_printIdent();

	// Label print
	printf( "l_%d:", lid );

	// last id control
	g_lastOpenLabel = lid;
}


// Generate code for: jump to lid
void code_jumpLabel( int lid ) {
	code_printIdent();
	printf( "br label %%l_%d", lid );
}


// Generate code for: end current label with: a jump to lid if lid >= 0
// Only needed to end a label early, with a jump that is not to the next label
void code_endLabelWJumpTo( int lid ) {
	g_lastOpenLabel = -1;

	if ( g_lid >= 0 ) {
		code_jumpLabel( lid );
	}
}


// Generate code for: open a new label, returns the ID of the new label
int code_startLabel( void ) {
	int labelID;

	// new id control
	labelID = codeAux_getNewLabel();

	// If theres an opened label, finish it with a jump for this new label
	if ( g_lastOpenLabel >= 0 ) {
		code_endLabelWJumpTo( labelID );
	}

	// Print Label itself
	code_label( labelID );

	return labelID;
}

// Generate code for: <var1> = <var2>
// Useful for: LLVM Local Var duplication in branches
void code_LLVMvarCopy( int type , int destinationID , int originIndex , int* varTracking ) {
	int id2 = varTracking[originIndex];
	
	code_printIdent();
	
	code_llvmID_LOC( destinationID );
	
	printf( " = " );
	
	code_ArithmeticType( type , '+' ); 
	
	// ZERO
	type == FLOAT ? printf(" 0.0 ") : printf(" 0 ");
	printf(" , ");

	// Origin Reference Type
	code_llvmID_IDX( originIndex , varTracking );
}

// -----------------------------------------------------------------------------------------------------

void codeCond( ABS_node* exp, int label1, int label2 , int* varTracking );
int codeExp( ABS_node* exp , int* varTracking ) ;
/*
 * Returns the ID of a i1 variable which contains the result of the expression
 * TRUE/FALSE
 */


int codeCondEval( ABS_node* exp , int* varTracking ) {
	int labelTrue = codeAux_getNewLabel();
	int labelFalse = codeAux_getNewLabel();
	switch ( exp->tag ) {
	case EXP_ANDOR:
	case EXP_NOT: {
		codeCond( exp, labelTrue, labelFalse , varTracking );
		break;
	}
	case EXP_COMP: {
		//Avaliate the expression and then do the branch

		//icmp <eq/ne/sgt/sge/slt/sle> %1 %2
		//Evaluate exp1 for %1
		//Evaluate exp2 for %2
		//find the operation <eq/ne/sgt/sge/slt/sle>
		//write the cmp
		//write the branch using the cmp
		int id1 , id2;
		int type;
		int operation;
		ABS_node* exp1;
		ABS_node* exp2;

		operation 	= exp->node.exp.data.operexp.opr;
		exp1 		= exp->node.exp.data.operexp.exp1;
		exp2 		= exp->node.exp.data.operexp.exp2;
		type 		= exp1->node.exp.type;

		id1 = codeExp( exp1 , varTracking );
		id2 = codeExp( exp2 , varTracking );

		// Start of the comparison line
		code_printIdent();
		int resultId = code_newVar();
		printf( " = " );

		// Operation Type
		switch ( type ) {
		case INT:
			printf( "icmp " );
			operation != TK_CE ? printf( "s" ) : 0 ; // Stray case, wtf clang?
			break;

		case FLOAT:
			printf( "fcmp o" );
			break;
		}

		// Operation
		switch ( operation ) {
		case TK_CE:
			printf( "eq" );
			break;

		case TK_GE:
			printf( "ge" );
			break;

		case '>':
			printf( "gt" );
			break;

		case TK_LE:
			printf( "le" );
			break;

		case '<':
			printf( "lt" );
			break;
		}
		printf( " " );

		// Result Type
		code_type( type );
		printf( " " );

		// Operator1
		code_nodeRepresentation( exp1 , id1 );
		printf( " , " );

		// Operator2
		code_nodeRepresentation( exp2 , id2 );
		return resultId;
	}

	default: {
		// TODO: Tratar literal
		int expid = codeExp( exp , varTracking );
		// %answer = i1
		code_printIdent();
		int resultId = code_newVar();
		switch ( exp->node.exp.type ) {
		case INT: {
			printf( " = icmp ne i32 0, " );
			break;
		}
		case FLOAT: {
			printf( " = fcmp une float 0, " );
			break;
		}
		}
		code_llvmID_LOC( expid );
		return resultId;
	}
	}
	int labelPhi = codeAux_getNewLabel();
	code_label( labelTrue );
	code_jumpLabel( labelPhi );
	code_label( labelFalse );
	code_jumpLabel( labelPhi );
	code_label( labelPhi );
	code_printIdent();
	int resultId = code_newVar();
	printf( " = phi i1 [1,%%l_%d], [0,%%l_%d]", labelTrue, labelFalse );
	return resultId;

}
/* Generate code for the evaluation of a conditional (for ifs and whiles)
 * Returns the id of the variable that contains the evaluation of the conditional
 */
void codeCond( ABS_node* exp, int label1, int label2 , int* varTracking ) {
	switch ( exp->tag ) {
	case EXP_ANDOR: {
		switch ( exp->node.exp.data.operexp.opr ) {
		case TK_AND: {
			int labelID = codeAux_getNewLabel();
			codeCond( exp->node.exp.data.operexp.exp1, labelID, label2 , varTracking );
			code_label( labelID );
			codeCond( exp->node.exp.data.operexp.exp2, label1, label2 , varTracking );
			break;
		}
		case TK_OR: {
			int labelID = codeAux_getNewLabel();
			codeCond( exp->node.exp.data.operexp.exp1, label1, labelID , varTracking );
			code_label( labelID );
			codeCond( exp->node.exp.data.operexp.exp2, label1, label2, varTracking );
			break;
		}
		}
		break;
	}

	case EXP_NOT: {
		codeCond( exp->node.exp.data.operexp.exp1, label2, label1, varTracking );
		break;
	}
	default: {
		//ALL THE REST
		//Maybe get the value?
		int condid = codeCondEval( exp, varTracking );
		code_printIdent();
		printf( "br i1 " );
		code_llvmID_LOC( condid );
		printf( ", label " );
		code_llvmLabel( label1 );
		printf( ", label " );
		code_llvmLabel( label2 );
		break;
	}
	}
}

//Evaluates an expression and attributes it to a temporary

void exp_eval( ABS_node* exp, int tempID ) {
	//TODO:
	//get a new temporary
	/*store the literal into the variable or
	 * perform all the operations and then
	 * store into the variable. Which would
	 * mean just passing tempID onwards.
	 */
}

//Evaluates an expression into a conditional value
void cond_eval( ABS_node* exp, int tempID ) {
	// TODO:
	/*
	 * maybe get the expression from exp_eval and
	 * then just checking if the value is zero or no
	 * will need a new temp probably
	 */
}




// --------------------------------------------------------------------
// Main Code
// --------------------------------------------------------------------

void genCode_list( 	ABS_node* node , 	int* varTracking );
void genCode( 		ABS_node* node , 	int* varTracking );
void codeDecl( 		ABS_node* node , 	int* varTracking );
void codeDeclFunc( 	ABS_node* node , 	int* varTracking );
void codeDeclVar( 	ABS_node* node , 	int* varTracking );
void codeParam( 	ABS_node* param , 	int* varTracking );
void codeFuncBody( 	ABS_node* block , 	int* varTracking );
void codeVarDecl( 	ABS_node* decl , 	int* varTracking );
void codeCmd( 		ABS_node* cmd , 	int* varTracking );
int codeExp( 		ABS_node* exp , 	int* varTracking );
void codeCmd_ret( 	ABS_node* cmd , 	int* varTracking );
int codeCmd_atr( 	ABS_node* cmd , 	int* varTracking );
                   
int codeArithmeticResult( int resultType , int operation , ABS_node* operator1 ,
                    ABS_node* operator2 , int* varTracking );

// --------------------

void genASTCode( void ) {
	ABS_node* thisNode = programNode;

	// Create Variable Change Tracking control
	int varTracking[VAR_ARRAY_SIZE];
		
	// Root of the program is global:
	// Set global state
	codeAux_enterGlobalScope();
	
	// Code Generation
	genCode_list( thisNode , varTracking );
}


void genCode_list( ABS_node* node , int* varTracking ) {
	while ( node != NULL ) {
		genCode( node , varTracking );
		node = node->next;
	}
}


void genCode( ABS_node* node , int* varTracking ) {
	switch ( node->type ) {
	case TYPE_DECL:
		return codeDecl( node , varTracking );

	case TYPE_ID:
	//return genCode_id( node );

	case TYPE_EXP:
	//return genCode_exp( node );

	case TYPE_VAR:
	//return genCode_var( node );

	case TYPE_CMD:
		return codeCmd( node , varTracking );

	default:
		return;
	}
}


/*
 * Create PHI for the end of IF code
 */
void codeIfPhi( int orignLabel , int thenLabel , int elseLabel ,
                int* startTracker , int* thenTracker , int* elseTracker , int limit ) {
	int i;
	int phiId;

	for ( i = 0 ; i < limit ; i++ ) {
		if ( thenTracker[i] != elseTracker[i] ) {
			// Variable changed
			code_printIdent();
			phiId = code_newVar();
			printf( " = phi " );
			code_type( g_typeTracking[i] );
			printf( " " );

			// Then Branch Check
			printf( "[" );
			if ( thenTracker[i] >= 0 ) {
				// Changed in the then branch
				code_llvmID_LOC( thenTracker[i] );
				printf( " , " );
				code_llvmLabel( thenLabel );
			}
			else {
				// Not changed, use the starting reference instead
				code_llvmID_LOC( startTracker[i] );
				printf( " , " );
				code_llvmLabel( orignLabel );
			}
			printf( "]" );

			printf( " , " );

			printf( "[" );
			// Else Branch Check
			if ( elseTracker[i] >= 0 ) {
				// Changed in the else branch
				code_llvmID_LOC( elseTracker[i] );
				printf( " , " );
				code_llvmLabel( elseLabel );
			}
			else {
				// Not changed, use the starting reference instead
				code_llvmID_LOC( startTracker[i] );
				printf( " , " );
				code_llvmLabel( orignLabel );
			}
			printf( "]" );

			// Update the original Tracker
			startTracker[i] = phiId;
		}
	}
}

void codeWhilePhi( int originLabel, int blockLabel, int* startTracker,
                   int* phiTracker, int* blockTracker, int limit ) {
                   
	int phiId;
	
	// Look for changed/PHIs 
	// ps: LLVM states that PHI comes at top of the BLOCK
	for ( int i = 0; i < limit; i++ ) {	
		if ( blockTracker[i] != phiTracker[i] ) {
			code_printIdent();
			code_llvmID_LOC( phiTracker[i] );
				
			// Variable changed, phi is needed
			printf( " = phi " );
			code_type( g_typeTracking[i] );
			printf( " " );
			
			// Block branch merge
			printf( "[" );
			code_llvmID_LOC( blockTracker[i] );
			printf( " , " );
			code_llvmLabel( blockLabel );
			printf( "] , [" );
			code_llvmID_LOC( startTracker[i] );
			printf( " , " );
			code_llvmLabel( originLabel );
			printf( "]" );
			
			// Update origin tracker
			startTracker[i] = phiTracker[i];
		}
	}
	
	// Look for not changed ( or global )
	for ( int i = 0; i < limit; i++ ) {	
		if ( blockTracker[i] == phiTracker[i] ) {
			// Variable not changed or is global
			// But we could have used PHI reference, we need to set its value
			code_LLVMvarCopy( g_typeTracking[i] , phiTracker[i] , i , startTracker );	
		}
	}
}

/*
 * generates code for declarationsgetelementptr
 */

void codeDecl( ABS_node* node , int* varTracking ) {
	switch ( node->tag ) {
	case DEC_FUNC: {
		codeDeclFunc( node , varTracking );
		break;
	}
	case DEC_VAR: {
		codeDeclVar( node , varTracking );
		break;
	}
	}
}


/*
 * generates code for variable definition
 * for SSA no code is need, but the state needs to be set
 * Globals dont follow SSA rule.
 */
void codeDeclVar( ABS_node* node , int* varTracking ) {
	int trackIndex;
	
	// Give the variable a track index
	trackIndex = track_setVarRef( node );

	// Check code scope state
	if( g_globalScope ) { 
		// The code is in Global Scope
		int iType , size , id;
		// Generate new ID
		id = codeAux_newVid();
		track_setVarId( node , varTracking , id );		
		
		// Type and Size
		iType = g_typeTracking[trackIndex];
		size = 	codeAux_getSize( iType );
	
		// Code Line
		code_printIdent();
		code_llvmID_GLB( id );
		printf(" = common global ");
		code_type( iType );
		printf(" 0 , align %d" , size );
		
		// Control
		g_lastGlobalIndex = id;
	}
	else {
		// The code is in a Local Scope
		// Mark the variable to "declared but not initialized"
		track_setVarId( node , varTracking , VAR_NOT_INITIALIZED );
	}
}



/*
 * generates code for function definiton
 */
void codeDeclFunc( ABS_node* node , int* varTracking ) {
	char* type = codeAux_getType( node->node.decl.funcdecl.type );
	const char* func_name = codeAux_getNodeName( node ); //@func_name

	// Prepare Global Variables
	codeAux_resetFuncGlobals();
	codeAux_exitGlobalScope( varTracking );

	// Function LLVM Code
	code_printIdent();
	printf( "\ndefine %s @%s", type, func_name );

	codeParam( node->node.decl.funcdecl.param , varTracking );

	codeFuncBody( node->node.decl.funcdecl.block , varTracking );

	// Restore Tracking Index
	codeAux_enterGlobalScope();
}


/*
 * prints the parameters in the llvm format
 */
void codeParam( ABS_node* param , int* varTracking ) {
	int oId , dId;
	int refId , tId;
	char* type;
	char* id;
	ABS_node* sParam = param;
	int  commaFlag = 0;

	printf( "( " );

	while ( param != NULL ) {
		type = codeAux_getType( param->node.decl.vardecl.type );

		// Annoying Separator Flag
		if ( commaFlag ) {
			printf( " , " );
		}
		else {
			commaFlag = 1;
		}

		//g_nextVarRefIndex

		// Var ID and Type
		printf( "%s ", type );
		tId = code_newVar();
		track_setVarRef( param );
		track_setVarId( param , varTracking , tId );

		param = param->next;
	}

	printf( " )" );
}


/*
 * generates code for the body of the function
 */

void codeFuncBody( ABS_node* block , int* varTracking ) {
	code_printIdented( "{" );
	codeAux_enterBlock();

	code_startLabel();

	code_printIdented( "; Declarations" );
	genCode_list( block->node.cmd.blockcmd.decl , varTracking );

	code_printIdented( "; Commands" );
	genCode_list( block->node.cmd.blockcmd.cmd , varTracking );

	codeAux_exitBlock();

	code_printIdented( "}\n" );
}


/*
 * generates code for a block
 */

void codeBlock( ABS_node* block , int* varTracking ) {
	int declaredLimit = g_nextVarRefIndex;
	codeAux_enterBlock();

	genCode_list( block->node.cmd.blockcmd.decl , varTracking );
	genCode_list( block->node.cmd.blockcmd.cmd , varTracking );

	codeAux_exitBlock();
	g_nextVarRefIndex = declaredLimit; // Discard declarations inside the block
}


/*
 * generates code for commands
 */
void codeCmd( ABS_node* cmd , int* varTracking ) {
	switch ( cmd->tag ) {
	case CMD_RET: {
		codeCmd_ret( cmd , varTracking );
		break;
	}

	case CMD_ATTR: {
		codeCmd_atr( cmd , varTracking );
		break;
	}

	case CMD_BLOCK: {
		codeBlock( cmd , varTracking );
		break;
	}

	case CMD_IF: {
		// cmd->node.cmd.ifcmd.(exp,cmd1,cmd2)
		int expId;
		int thenLabel;
		int elseLabel;
		int startLabel;
		int phiLabel;

		int thenLastLabel;
		int elseLastLabel;

		int declaredLimit;

		int varTrackingThen[VAR_ARRAY_SIZE];
		int varTrackingElse[VAR_ARRAY_SIZE];

		// LLVM Commentary
		code_printIdented( "; IF" );

		// Generate label IDs
		startLabel  = g_lastOpenLabel;
		thenLabel 	= codeAux_getNewLabel();
		elseLabel 	= codeAux_getNewLabel();
		phiLabel 	= codeAux_getNewLabel();

		// Copy Tracking Arrays
		codeAux_copyTrackingArray( varTrackingThen , varTracking );
		codeAux_copyTrackingArray( varTrackingElse , varTracking );
		declaredLimit = g_nextVarRefIndex;

		// Code Cond
		codeCond( cmd->node.cmd.ifcmd.exp, thenLabel, elseLabel , varTracking );


		// Then Label Block
		code_label( thenLabel );
		genCode_list( cmd->node.cmd.ifcmd.cmd1 , varTrackingThen );
		thenLastLabel = g_lastOpenLabel;
		code_endLabelWJumpTo( phiLabel );

		// Else Label Block
		code_label( elseLabel );
		genCode_list( cmd->node.cmd.ifcmd.cmd2 , varTrackingElse );
		elseLastLabel = g_lastOpenLabel;
		code_endLabelWJumpTo( phiLabel );


		// Phi Block -> PHI
		code_label( phiLabel );
		codeIfPhi( startLabel , thenLastLabel , elseLastLabel , varTracking ,
		           varTrackingThen , varTrackingElse , declaredLimit );
		g_nextVarRefIndex = declaredLimit;

		break;
	}

	case CMD_WHILE: {
		int i;
		
		int labelStart 	= g_lastOpenLabel;
		int labelCond 	= codeAux_getNewLabel();
		int labelBlock 	= codeAux_getNewLabel();
		int labelEnd 	= codeAux_getNewLabel();
		int labelPhi 	= codeAux_getNewLabel();

		int declaredLimit;

		int varTrackingBlock[VAR_ARRAY_SIZE];
		int varTrackingPhi[VAR_ARRAY_SIZE];		

		code_printIdented( "; WHILE" );
		
		// Register last index declared before While Block Scope
		declaredLimit = g_nextVarRefIndex;
		
		// Prepare Tracking Arrays
		// Generate IDs to be used in PHI block
		// Why? Break cyclic relationship between PHI Block and WhileBody Block
		for( i = 0 ; i < declaredLimit ; i++ ) {
			varTrackingPhi[i] = codeAux_newVid();
		}
		codeAux_copyTrackingArray( varTrackingBlock, varTrackingPhi );
		code_endLabelWJumpTo( labelPhi );
		
		// Condition Block
		code_label( labelCond );
		printf( "\t; WHILE - Condition Block" );				
		codeCond( cmd->node.cmd.whilecmd.exp, labelBlock, labelEnd, varTrackingPhi );
		
		// While Body Block		
		code_label( labelBlock );
		printf( "\t; WHILE - Body Block" );		
		genCode_list( cmd->node.cmd.whilecmd.cmd, varTrackingBlock );
		labelBlock = g_lastOpenLabel; // CHECK : PQ?
		code_jumpLabel( labelPhi );
		
		// Phi Block
		code_label( labelPhi );
		printf( "\t; WHILE - PHI Block" );				
		codeWhilePhi( labelStart, labelBlock , varTracking, varTrackingPhi, 
				varTrackingBlock, declaredLimit );
		              
		// End block          
		code_endLabelWJumpTo( labelCond );
		code_label( labelEnd );
				
		// Restore last index declared before While Block Scope
		g_nextVarRefIndex = declaredLimit; // CHECK: G: Why? R: Discard indexes declared in the while scope
		break;
	}
	}
}

/*
 * generates code for exp
 */

int codeExp( ABS_node* exp , int* varTracking ) {
	int id;
	int size;
	char* type;

	switch ( exp->tag ) {
	case EXP_VAR: {
		int trackIndex;
		int tId;
		
		trackIndex = track_getVarRef( exp );
		tId = track_getVarId( exp , varTracking );

		// Check initialization
		if ( tId < 0 ) {
			TOL_error( "Variable referenced before initialization" , exp->line ,
			           codeAux_getNodeName( exp ) );
		}
		
		// Global transformation to temporary local
		if( trackIndex <= g_lastGlobalIndex ) {
			// Load global
			id = code_load( trackIndex , varTracking );	
		}
		else {
			// Return expression result
			id = tId;
		}

		break;
	}

	case CAST: {
		int castID = codeExp( exp->node.exp.data.cast , varTracking );
		code_printIdent();
		id = code_newVar();
		printf( " = sitofp " );
		code_nodeType( exp->node.exp.data.cast );
		printf( " " );
		code_nodeRepresentation( exp->node.exp.data.cast , castID );
		printf( " to " );
		code_type( exp->node.exp.type );
		break;
	}

	case EXP_ARIT: {
		int type;
		int operation;
		ABS_node* exp1;
		ABS_node* exp2;

		type 		= exp->node.exp.type;
		operation 	= exp->node.exp.data.operexp.opr;
		exp1 		= exp->node.exp.data.operexp.exp1;
		exp2 		= exp->node.exp.data.operexp.exp2;

		id = codeArithmeticResult( type , operation , exp1 , exp2 , varTracking );

		break;
	}


	case EXP_COMP:
	case EXP_ANDOR: {
		int condid = codeCondEval( exp, varTracking );
		code_printIdent();
		id = code_newVar();
		printf( " = zext i1 " );
		code_llvmID_LOC( condid );
		printf( " to " );
		switch ( exp->node.exp.type ) {
		case INT: {
			printf( "i32" );
			break;
		}
		case FLOAT: {
			printf( "float" );
			break;
		}
		}
		break;
	}

	case EXP_CALL: {
		const char* fName;
		ABS_node* 	argExp;

		char*	argType;
		int 	argId;
		int*	argVars;
		int 	i;

		int commaFlag = 0;

		type = codeAux_getType( exp->node.exp.type );
		fName = codeAux_getNodeName( exp );

		// LLVM Comment
		code_printIdent();
		printf( "; Function Call: %s" , fName );

		// Discover qty of args
		for ( argExp = exp->node.exp.data.callexp.exp2 , i = 0 ; argExp != NULL ;
		        argExp = argExp->next , i++ );

		// Alloc size
		argVars = ( int* )malloc( sizeof( int ) * i );

		// Generate Arguments Variables
		for ( argExp = exp->node.exp.data.callexp.exp2 , i = 0 ; argExp != NULL ;
		        argExp = argExp->next , i++ ) {
			argType = codeAux_getType( argExp->node.exp.type );

			switch ( argExp->tag ) {
			case LIT_INT:
			case LIT_FLOAT:
			case LIT_STRING: {
				argVars[i] = track_getVarId( argExp , varTracking );
				break;
			}

			default:
				argVars[i] = codeExp( argExp , varTracking );
				break;
			}
		}

		// Call code
		code_printIdent();
		id = code_newVar();

		printf( " = call %s @%s(" , type , fName );

		// Arguments code
		i = 0;
		for ( argExp = exp->node.exp.data.callexp.exp2 ; argExp != NULL ;
		        argExp = argExp->next ) {
			// Annoying Separator Flag
			if ( commaFlag ) {
				printf( " , " );
			}
			else {
				commaFlag = 1;
			}

			// Arg Reference
			code_nodeType( argExp );
			printf( " " );
			code_nodeRepresentation( argExp , argVars[i] );

			// argVars index
			i++;
		}


		printf( ")" );

		break;
	}

	case LIT_FLOAT:
	case LIT_INT: {
		id = -1;
		break;
	}

	}

	return id;
}


// Generate code for: LLVM arit expression with atribuition to a Local ID
// Returns ID of the Local with the result
int codeArithmeticResult( int resultType , int operation , ABS_node* operator1 ,
                    ABS_node* operator2 , int* varTracking ) {
	int 	id;
	int 	id1;
	int 	id2;

	// Generate code for both operators
	operator1 ? id1 = codeExp( operator1 , varTracking ) : 0;
	operator2 ? id2 = codeExp( operator2 , varTracking ) : 0;

	// Result Variable	
	code_printIdent();
	id = code_newVar();
	printf( " = " );
	
	// operation name and type
	code_ArithmeticType( resultType , operation );

	// Reference 1
	operator1 ? code_nodeRepresentation( operator1 , id1 ) : printf( "0" );

	// Separator
	printf( " , " );

	// Reference 2
	operator2 ? code_nodeRepresentation( operator2 , id2 ) : printf( "0" );   	

	return id;
}


/*
 * generates code for return
 */
void codeCmd_ret( ABS_node* cmd , int* varTracking ) {
	char* type 	= codeAux_getType( cmd->node.cmd.retcmd.type );
	int id 		= codeExp( cmd->node.cmd.retcmd.exp , varTracking );

	code_printIdented( "; Return" );

	code_printIdent();
	printf( "ret " );
	code_type( cmd->node.cmd.retcmd.type );
	printf( " " );
	code_nodeRepresentation( cmd->node.cmd.retcmd.exp , id );
}


/*
 * generates code for attribution
 */
int codeCmd_atr( ABS_node* cmd , int* varTracking ) {
	int retId , expId;
	int iVarType;
	int trackIndex;

	ABS_node* var = cmd->node.cmd.attrcmd.var;
	ABS_node* exp = cmd->node.cmd.attrcmd.exp;

	// Get left side info ( var )
	if ( var->tag == VAR_MONO ) {
		iVarType = var->node.var.type;
	} else {
		// TODO: Array
	}

	// Generate attribution code
	switch ( exp->tag ) {
	case LIT_INT:
	case LIT_FLOAT:
		retId = codeArithmeticResult( iVarType , '+' , NULL , exp , varTracking );
		break;

	default:
		retId = codeExp( exp , varTracking );
		break;
	
	}

	// Get Variable Track Index
	trackIndex = track_getVarRef( var );	
	
	// Decide if variable is Local or Global
	if( trackIndex > g_lastGlobalIndex ) {
		// SSA local, no need for extra code
		// Set the new ID
		track_setVarId( var , varTracking , retId );
	}
	else {
		// Global
		code_store( retId , trackIndex , varTracking );
	}

	return retId;
}

// Ultimo push

