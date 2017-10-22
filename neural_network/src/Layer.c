#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Neuron.h"
#include "Layer.h"
#include "InputLayer.h"

Layer * new_Layer (int non, int nopn, NeuronType nt)
{
	Layer * layer;
	layer = malloc(sizeof(Layer));

	layer->numofneurons = non;
	layer->numofprevneurons = nopn;
	layer->neurons = malloc(non * sizeof(Neuron *));
	double ** weights = layer_weightInitialize(layer, MEMORYMODE_GET, nt);

	for (int i = 0; i < non; i++)
	{
		double * tempWeights = malloc(non * sizeof(double));
		for (int j = 0; j < nopn; j++)
			tempWeights[j] = weights[i][j];
		layer->neurons[i] = new_Neuron(NULL, tempWeights, nopn, nt);
	}

	return layer;
}

void layer_setData (Layer * layer, double * data)
{
	for (int i = 0; i < layer->numofneurons; i++)
		layer->neurons[i]->inputs = data;
}

double ** layer_weightInitialize (Layer * layer, MemoryMode mm, NeuronType nt)
{
	double ** weights = malloc(layer->numofneurons * sizeof(double *));
	double * memoryWeights = malloc(layer->numofprevneurons * sizeof(double));

	for (int i = 0; i < layer->numofneurons; i++)
		weights[i] = malloc(layer->numofprevneurons * sizeof(double));
	printf("%s weights are being initialized...\n",
			nt == NEURONTYPE_HIDDEN ? "Hidden" : "Output");
	// TODO: loading XML document and document element
	char * typename = (nt == NEURONTYPE_HIDDEN ? "Hidden" : "Output"); 
	char * filename = malloc(strlen(typename) + strlen("_memory.data") + 1);
	memcpy(filename, typename, strlen(typename));
	memcpy(filename + strlen(typename), "_memory.data", strlen("_memory.data"));
	filename[strlen(typename) + strlen("_memory.data") + 1] = '\0';
	printf("Trying to open %s.\n", filename);
	FILE * fw = fopen(filename, "r+");
	if (!fw)
	{
		printf("File %s is not exists.\n", filename);
		fw = fopen(filename, "w");
		srand(time(NULL));
		for (int i = 0; i < layer->numofprevneurons - 1; i++)
			fprintf(fw, "%f,", 1.0 / (double) (rand() % 100000));
		fprintf(fw, "%f", 1.0 / (double) (rand() % 100000));
		fclose(fw);
	}
	fw = fopen(filename, "r+");
	if (!fw) exit(1);
	printf("File %s was opened successfully.\n", filename);
	for (int i = 0; i < layer->numofprevneurons; i++)
	{
		char * buf = malloc(512);
		int j;
		for (j = 0; (buf[j] = fgetc(fw)) != EOF && buf[j] != ','; j++);
		if (buf[j] == EOF && i < layer->numofprevneurons - 1) exit(1);
		buf[j] = '\0';
		memoryWeights[i] = atof(buf);
	}
	fclose(fw);
	// END
	switch (mm)
	{
		case MEMORYMODE_GET:
			for (int i = 0; i < layer->numofneurons; i++)
				for (int j = 0; j < layer->numofprevneurons; j++)
					weights[i][j] = memoryWeights[layer->numofprevneurons * i + j];
			break;
		case MEMORYMODE_SET:
			for (int i = 0; i < layer->numofneurons; i++)
				for (int j = 0; j < layer->numofprevneurons; j++)
					memoryWeights[i * layer->numofprevneurons + j] = layer->neurons[i]->weights[j];
			break;
	}
	// TODO: saving XML document
	fw = fopen(filename, "w");
	for (int i = 0; i < layer->numofprevneurons - 1; i++)
		fprintf(fw, "%f,", memoryWeights[i]);
	fprintf(fw, "%f", memoryWeights[layer->numofprevneurons - 1]);
	fclose(fw);
	// END
	printf("%s weights have been initialized...\n",
			nt == NEURONTYPE_HIDDEN ? "Hidden" : "Output");

	return weights;
}
