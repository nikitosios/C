#include <stdio.h>

#define Pi 3.14

float R;
double res;

void main (void)
{
	printf("Радиус: ");
	scanf("%f", &R);
	res=R*R*Pi;
	printf("Площадь: %f.\n", res);
	return;
}

