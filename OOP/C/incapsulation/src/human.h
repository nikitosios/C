#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct human {
	char *name;
	unsigned char age;
	void (*say) (struct human *, char *);
	struct son *(*makeChild) (struct human *);
} human;

typedef struct son { // будет наследовать объект human
	struct human *hum;
	char *father;
} son;

static void say (struct human *, char *);
struct human *newHuman (void);
void killHuman (struct human *);
static son *makeChild (struct human *);
