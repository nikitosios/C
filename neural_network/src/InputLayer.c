#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "InputLayer.h"

char * getImage (char * url)
{
	char * image;
	image = malloc(1920 * 1080 * 3 * sizeof(char));
	FILE * fd;
	fd = fopen(url, "r");
	if (!fd)
	{
		printf("File %s is not exists.\n", url);
		exit(1);
	}

	fseek(fd, 54, SEEK_SET);
	for (int i = 0; i < 1920 * 1080; i++)
	{
		image[i * 3 + 2] = fgetc(fd);
		image[i * 3 + 1] = fgetc(fd);
		image[i * 3 + 0] = fgetc(fd);
	}

	fclose(fd);
	return image;
}

InputLayer * new_InputLayer (void)
{
	InputLayer * layer = malloc(sizeof(InputLayer));
	
	char numofletters = 'Z' - 'A' + 1;
	char ** url = malloc(numofletters * sizeof(char *));
	layer->trainset = malloc(numofletters * sizeof(Tuple *));
	for (int i = 0; i < numofletters; i++)
	{
		layer->trainset[i] = malloc(sizeof(Tuple));
		layer->trainset[i]->a1 = malloc(1920 * 1080 * 3 * sizeof(double));
		layer->trainset[i]->a2 = malloc(1920 * 1080 * 3 * sizeof(double));
	}
	char c = 'A';
	FILE * fd = fopen("trainset", "r");
	for (int i = 0; i < numofletters; i++)
	{
		char buffer[256], ch;
		int j;
		for (j = 0; (ch = fgetc(fd)) != ' ' && ch != EOF && ch != '\n'; j++)
			buffer[j] = ch;
		buffer[j] = '\0';
		url[i] = malloc(strlen(buffer) + 1);
		memcpy(url[i], buffer, strlen(buffer) + 1);
		c++;
		printf("URL %s is loaded.\n", url[i]);
	}
	fclose(fd);
	for (int i = 0; i < numofletters; i++) {
		int j = 0;
		char * pb = getImage(url[i]);
		for (int y = 0; y < 1080; y++)
			for (int x = 0; x < 1920; x++)
				for (int c = 0; c < 3; c++, j++)
					layer->trainset[i]->a1[j] = pb[y * 1920 * 3 + x * 3 + c];
		for (j = 0; j < numofletters; j++)
			layer->trainset[i]->a2[j] = i == j ? 1.0 : 0.0;
		printf("Image %s is loaded.\n", url[i]);
	}

	return layer;
}
