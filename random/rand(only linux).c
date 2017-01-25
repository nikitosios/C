#include <stdio.h>

int main (void)
{
	FILE *urandom;
	
	urandom = fopen("/dev/urandom", "r");
	printf("%i\n", fgetc(urandom)%10+1);
	fclose(urandom);
	return 0;
}

