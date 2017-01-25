#include <stdio.h>

char op;
float x,y;
int midvar;

void reading (void)
{
	start:
	printf("op:\n1 - add\n2 - subtract\n3 - multiply\n4 - divide\n>");
	scanf("%d", &midvar);
	op=midvar;
	if ((op<1)||(op>4)) {
		goto start;
	}
	printf("x=");
	scanf("%e", &x);
	switch(op)
	{
		case 1: printf("+\n"); break;
		case 2: printf("-\n"); break;
		case 3: printf("*\n"); break;
		case 4: printf("/\n"); break;
	}
	printf("y=");
	scanf("%e", &y);
	return;
}

double calcing (void)
{
	switch(op)
	{
		case 1: return x+y; break;
		case 2: return x-y; break;
		case 3: return x*y; break;
		case 4: return x/y; break;
	} 
}

void printing (double arg)
{
	printf("=%e\n", arg);
	return;
}

void main (void)
{
	reading();
	printing(calcing());
	return;
}

