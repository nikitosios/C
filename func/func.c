#include <stdio.h>

unsigned short sum (char a, char b)
{
	return a+b;
}

short sub (char x, char y)
{
	return x-y;
}

void main (void)
{
	printf("\nSub of 5 ans 2 is %i.\n", sub(5, 2));
	printf("\nSum of 5 and 2 is %i.\n\n", sum(5, 2));
	return;
}

