#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float monga_float(float a);

int main(void) {
	float f;

	printf("\nCalling monga_float(10.0)" );
	printf("\nreturn:\n");
	
	f = monga_float(10.0);
	printf("%f",f);
	
	printf("\n\n");
	
	return 0;
}
