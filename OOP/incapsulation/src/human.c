#include "human.h"

static void say (struct human *this, char *msg)
{
	printf("%s: %s\n", this->name, msg);
}

human *newHuman (void)
{
	struct human *hum;
	char *defaultName = "Вася";
	
	hum = malloc(sizeof(struct human));
	hum->say = (void *) &say;
	hum->age = 20;
	hum->name = malloc(20);
	for (int i = 0; i < strlen(defaultName); ++i)
		hum->name[i] = defaultName[i];
	printf("%s родился!\n", hum->name);
	return hum;
}

static son *makeChild (struct human *parent)
{
	struct son *s;
	char *stdName = "Валера";

	s = malloc(sizeof(son));
	s->father = malloc(20);
	for (int i = 0; i < strlen(parent->name); ++i)
		s->father[i] = parent->name[i];
	/*s->name = malloc(20);
	for (int i = 0; i < strlen(stdName); ++i)
		s->name[i] = stdName[i];
	 тут я обращаюсь к полю, которое есть в структуре human, через структуру son.
	 * Это, по сути, наследование 
	s->age = 0;
	s->say("Агу!");*/
	return s;
}

void killHuman (struct human *hum)
{
	char *name = malloc(strlen(hum->name));
	for (int i = 0; i < strlen(hum->name); ++i)
		name[i] = hum->name[i];
	free(hum->name);
	free(hum);
	printf("%s убит...\n", name);
}
