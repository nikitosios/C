#include <stdio.h>

char hello1[] = { 'H', 'e', 'l', 'l', 'o', '1', '\0' };
char hello2[] = "Hello2";
const char * hello3 = "Hello3";
const char * const hello4 = "Hello4";

const char * states[] = { "Moscow", "New-York", "Kiev" }; 
// const char states[3][20] = { "", "", "" };
// const float * prices[] = { {0, 0}, {0, 0}, {0, 0} };
// const float prices[3][2] = { {0, 0}, {0, 0}, {0 ,0} };

void printArrayString (const char ** string)
{
	printString(*(states + 0));
	printString(*(states + 1));
	printString(*(states + 2));
	return;
}

void printString (const char * string)
{
	printf("\n%s", string);
	return;
}

void EOL ()
{
	printf("\n");
	return;
}

unsigned int checkAllowedFlags(const char ** const flags)
{
	// for || while
	printf("Bad Argument!");
	return 0;
}

const char * allowedFlags[] = { "--print", "--god-mode" };
const char * allowedArgs[] = { "-n", "-p", "-j" };

void main (int argc, const char ** const argv)
{
	if (argc > 1)
		checkAllowedFlags(argv);

	printf("\n%d", argc);
	printf("\n%s", argv[0]);
	printf("\n%s", argv[1]);
	printf("\n%s", argv[2]);

	/*printf("\nHello3: %p", hello3);
	printf("\nHello4: %p", hello4);
	
	hello3 = hello4;
	
	printString(hello3);
	printString(hello4);

	EOL();

	printf("\n%s", *(states + 0));
	printf("\n%s", *(states + 1));
	printf("\n%s", *(states + 2));

	printArrayString(states);*/

	printf("\n\n");
	return;
}

