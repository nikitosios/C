#include <stdio.h>

char getNumber (void)
{    
                    //  ---char---
     // return 255; // 1|11111111|   - переполнение, а b11111111 == -1
                    //  ----------
	return 127;
}

signed char getNegativeNumber (void)
{
	return -128;
}

unsigned char getPositiveNumber (void)
{
	return 255;
}

//----------------------------------------------------
// Для символов:                                     |
// char           -128 .. 127   10000000 .. 01111111 |
//---------------------------------------------------|
// Для чисел:                                        |
// signed char    -128 .. 127   10000000 .. 01111111 |
// unsigned char     0 .. 255   00000000 .. 11111111 |
//----------------------------------------------------

void main (void)
{
	printf("Positive number: %d.\n", getPositiveNumber());
	printf("Negative number: %d.\n", getNegativeNumber());
	printf("Number: %d.\n", getNumber());
	return;
}

