#ifndef TYPES_HEADER
#define TYPES_HEADER

// Monga Types
typedef enum typeEnum {
	CHAR,
	INT,
	FLOAT,
	STRING,
	VOID,
    TYPEQTY 
} TYP_typeEnum;



int TYP_getID(TYP_typeEnum type);
int TYP_array(int type);




#endif
