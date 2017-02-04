#include <stdio.h>

#define EOL '\n'

	char one = 1;
	char two = 2;
	char three = 3;
	char four = 4;
	char five = 5;

	char* oneP = NULL;
	char* twoP = NULL;
	char* threeP = NULL;
	char* fourP = NULL;
	char* fiveP = NULL;

void main (void)
{
	printf("%c", EOL);

	oneP = &one;
	twoP = &two;
	threeP = &three;
	fourP = &four;
	fiveP = &five;

	printf("One variable: %d%c", one, EOL);
	printf("Two variable: %d%c", two, EOL);
	printf("Three variable: %d%c", three, EOL);
	printf("Four variable: %d%c", four, EOL);
	printf("Five variable: %d%c", five, EOL);

	printf("%cOne address: %p", EOL, oneP);
	printf("%cTwo address: %p", EOL, twoP);
	printf("%cThree address: %p", EOL, threeP);
	printf("%cFour address: %p", EOL, fourP);
	printf("%cFive address: %p%c", EOL, fiveP, EOL);

	printf("%cOne value: %d%c", EOL, *oneP, EOL);
	printf("Two value: %d%c", *twoP, EOL);
	printf("Three value: %d%c", *threeP, EOL);
	printf("Four value: %d%c", *fourP, EOL);
	printf("Five value: %d", *fiveP);

	printf("%c%c", EOL, EOL);
	return;
}

