#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Neuron.h"

Neuron * new_Neuron (double * inputs, double * weights, size_t size, NeuronType type)
{
	Neuron * np;
	np = malloc(sizeof(Neuron));

	np->size = size;
	np->type = type;
	np->weights = malloc(size * sizeof(double));
	np->inputs = malloc(size * sizeof(double));

	for (size_t i = 0; i < size; i++)
		np->weights[i] = weights[i];
	for (size_t i = 0; i < size; i++)
		np->inputs[i] = inputs[i];

	return np;
}

double neuron_activate (Neuron * neuron, double * i, double * w, size_t size)
{
	double sum = 0;
	for (size_t j = 0; j < size; j++)
		sum += i[j] * w[j];
	return pow(1 + exp(- sum), -1);
}

double neuron_derivativate (Neuron * neuron, double out)
{
	return out * (1 - out);
}

double neuron_gradient (Neuron * neuron, double error, double dif, double g_sum)
{
	return neuron->type == NEURONTYPE_OUTPUT ? error * dif : g_sum * dif;
}

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

	for (int i = 0; i < layer->numofneurons; i++)
		weights[i] = malloc(layer->numofprevneurons * sizeof(double));
	printf("%s weights are being initialized...\n",
			nt == NEURONTYPE_HIDDEN ? "Hidden" : "Output");
	// TODO: loading XML document and document element
	char * filename = strcat(nt == NEURONTYPE_HIDDEN ? "Hidden" : "Output", "_memory.data");
	FILE * fw = fopen(filename, "r+");
	if (!fw)
	{
		fw = fopen(filename, "w");
		srand(time(NULL));
		for (int i = 0; i < layer->numofprevneurons - 1; i++)
			fprintf(fw, "%f,", 1.0 / (double) rand());
		fprintf(fw, "%f", 1.0 / (double) rand());
		fclose(fw);
	}
	fw = fopen(filename, "r+");
	if (!fw) exit(1);
	double * memoryWeights = malloc(layer->numofprevneurons * sizeof(double));
	for (int i = 0; i < layer->numofprevneurons; i++)
	{
		char buf[512];
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
