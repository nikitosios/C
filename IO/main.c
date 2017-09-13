#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main (void)
{
	char **p;
	char *numstr;
	int a = 7;
	int array[] = { 5, 45754, 564, 546, 32, 43, 52, 436 };

	/* stdlib.h */
	printf("%f\n", atof("99.4") * atoi("5") + atol("8723568368740"));
	printf("%f\n", strtod("99.4 243", p) * strtol("-3756634565", p, 10) + strtoul("10010010010010101001010101001010101001111001010101001", p, 2));
	srand(time(NULL));
	printf("%i\n", rand() % 10);
	
	return 0;
}
