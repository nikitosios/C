#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	char *variants[] = { "C", "C++", "C#", NULL };
	int variants_size, r;

	for (variants_size = 0; variants[variants_size] != NULL; ++variants_size);
	srand(time(NULL));
	r = rand() % variants_size;
	printf("%s\n", variants[r]);
	return 0;
}
