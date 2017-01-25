#include <stdio.h>
#include <time.h>

long int random (long int num)
{
	srand(time (NULL));
	num = rand()%num;
	return num;
}

int main (const int argc, const char ** const argv)
{
	printf("%i\n", random(10) + 1);
	return 0;
}

