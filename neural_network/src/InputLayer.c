#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "InputLayer.h"

InputLayer * new_InputLayer (void)
{
	char ** url = malloc(33 * sizeof(char *));
	trainset = malloc(33 * sizeof(Tuple *));
	for (int i = 0, char c = 'А'; i < 33; i++, c++)
	{
		printf("URL of the image of %c: ", c);
		scanf("%s", url[i]);
	}
	for (int i = 0; i < 33; i++) {
		/*
		pixbuf pb = getImage(url[i]);
		int j = 0;
		for (int x = 0; x < 1920; x++)
			for (int y = 0; y < 1080; y++)
				for (int c = 0; c < 3; c++, j++)
					trainset[i]->a1[j] = pb[x][y][c];
		*/
		for (j = 0; j < 33; j++)
			trainset[j] = i == j ? 1.0 : 0.0;
	}
}
