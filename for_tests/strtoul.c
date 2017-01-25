#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	char * string, * end;

	printf("\n\n%s\n", "Введите строку:");
	scanf("%s", string);
	printf("\nOutput: %i\n\n", strtoul(string, &end, 10));
	return 0;
}

