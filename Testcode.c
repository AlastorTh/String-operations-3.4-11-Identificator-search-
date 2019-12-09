#include "Header.h"


int func() {






	 int LOWER = 0;
	 int UPPER = 300;
	 int STEP = 20;
	float FAHR, CELSIUS;

	CELSIUS = LOWER;
	while (CELSIUS <= UPPER)
	{

		FAHR = (CELSIUS * (9.0 / 5.0)) + 32;
		printf("%4.0f %6.1f\n", CELSIUS, FAHR); // int test
		CELSIUS += STEP;
		return 0;
	}



}