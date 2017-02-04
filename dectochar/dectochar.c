#include <stdio.h>

int input;
char character, correct;

void incorrect (void)
{
	printf("Введенному числу не соответствует ни один символ таблицы ASCII, который можно вывести.\n");
	correct=1;
	return;
}

int main (void)
{
	start:
	correct=0;
	printf("Введите число от -128 до 127: ");
	scanf("%d", &input);
	if (input<33) {
		incorrect();
	}
	if (input>127) {
		incorrect();	
	}
	if (correct==1) {
		goto start;
	}
	character=input;
	printf("Согласно таблице символов ASCII, это...\n");
	printf("Символ %c!\n", character);
	return 0;
}

