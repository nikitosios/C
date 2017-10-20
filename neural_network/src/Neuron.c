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

double neuron_activator (Neuron * neuron, double * i, double * w, size_t size)
{
	double sum = 0;
	for (size_t j = 0; j < size; j++)
		sum += i[j] * w[j];
	return pow(1 + exp(- sum), -1);
}

double neuron_derivativator (Neuron * neuron, double out)
{
	return out * (1 - out);
}

double neuron_gradientor (Neuron * neuron, double error, double dif, double g_sum)
{
	return neuron->type == NEURONTYPE_OUTPUT ? error * dif : g_sum * dif;
}
