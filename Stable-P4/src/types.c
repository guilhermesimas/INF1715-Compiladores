#include "absSyntaxTree.h"
#include "types.h"

// Return the int id of the type
int TYP_getID(TYP_typeEnum type) {
	return type;
}

int TYP_array(int type){
    return type + TYPEQTY;
}
