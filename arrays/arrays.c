#include <stdio.h>

float price = 12.0f;
float prices[4] = { 1000.0f, 2000.0f, 3000.0f, 4000.0f };

void printArrayAddresses (float * arrayP)
{
	printf("\n\n0: %p\n", arrayP);
	printf("1: %p\n", arrayP+1);
	printf("2: %p\n", arrayP+2);
	printf("3: %p", arrayP+3);
	return;
}

int main (void)
{
	printf("\n");

	printf("[*] Index access:");
	printf("\n%s %10.2f", "Нулевой элемент массива:", prices[0]);
	printf("\n%s  %10.2f", "Первый элемент массива:", prices[1]);
	printf("\n%s  %10.2f", "Второй элемент массива:", prices[2]);
	printf("\n%s  %10.2f", "Третий элемент массива:", prices[3]);
	printf("\n\n[*] Pointer access:");
	printf("\n");
	printf("%s %10.2f\n", "Нулевой элемент массива:", *prices);
	printf("%s  %10.2f\n", "Первый элемент массива:", *(prices + 1));
	printf("%s  %10.2f\n", "Второй элемент массива:", *(prices + 2));
	printf("%s  %10.2f\n", "Третий элемент массива:", (prices + 3));
	size_t floatSize = sizeof(float);
	size_t intSize = sizeof(int);
	size_t charSize = sizeof(char);
	printf("\nSize of float type is      %zu bytes", floatSize);
	printf("\nSize of int type is        %zu bytes", intSize);
	printf("\nSize of char type is       %zu bytes", charSize);
	printf("\nSize of array is           %zu bytes", sizeof prices);
	printArrayAddresses(prices);	

	printf("\n\n");
	return 0;
}

