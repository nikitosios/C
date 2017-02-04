#include <stdio.h>
#include <stdbool.h>

#define SIZE 4

void printArray (int * array)
{
	unsigned char index = 0;
	while (index < SIZE)
	{
		printf("\n%d", *(array + index));
		index++;
	}
	return;
}

void printArrayByFor (int * array)
{
	for (unsigned char index = 0; index < SIZE; index++)
	{
		printf("\n%d", *(array + index));
	}
	return;
}

int main (void)
{
	int prices[SIZE] = { 100, 200, 300, 400 };
	
	bool isTrue = true;
	bool isFalse = false;

	printf("\n%d", *(prices + 0)); //   IT
	printf("\n%d", *(prices + 1)); //  IS A
	printf("\n%d", *(prices + 2)); //   BAD
	printf("\n%d", *(prices + 3)); //  IDEA
	printf("\n-----------------------------");
	printf("\nTrue: %d, False: %d", isTrue, isFalse);
	printf("\n-----------------------------");
	
	printf("\nPrinting array by while:");
	printArray(prices);
	printf("\n");
	printf("\nPrinting array by for:");
	printArrayByFor(prices);

	printf("\n\n");
	return 0;
}

