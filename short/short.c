#include <stdio.h>

unsigned short firstValue = 30000;
unsigned short secondValue = 20000;
signed short thirdValue = -30000;

//------------------------------------
// short [int]     -32 768 .. 32 767 |
// signed short    -32 768 .. 32 767 |
// unsigned short        0 .. 65 535 |
//------------------------------------

void main (void)
{
	
	printf("\n");	
	printf("%15s  %i\n", "First value:", firstValue);
	printf("%15s  %i\n", "Second value:", secondValue);
	printf("%15s %i\n", "Third value:", thirdValue);
	printf("\n");

	return;
}

