#include <stdio.h>

#include "human.h"

int main (void)
{
	struct human *vasya = newHuman();
	printf("%s уже вырос до %i лет.\n", vasya->name, vasya->age);
	vasya->say(vasya, "я даун!");
	struct son *vasyaSon = vasya->makeChild(vasya);
	printf("Сына назвали %s.", vasyaSon->name);
	killHuman(vasya);
	return 0;
}
