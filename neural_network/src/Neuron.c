#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "neuron.h"

Neuron new_Neuron (double * inputs, double * weights, size_t size, NeuronType type)
{
	Neuron np;
	np->sizex = sizex;
	np->sizey = sizey;
	np = malloc(sizeof(struct neuron));
	np->weight = malloc(sizex * sizeof(int *));
	for (int i = 0; i < sizex; i++) np->weight[i] = malloc(sizey * sizeof(int));
	np->mul = malloc(sizex * sizeof(int *));
	for (int i = 0; i < sizex; i++) np->mul[i] = malloc(sizey * sizeof(int));
	np->input = malloc(sizex * sizeof(int *));
	for (int i = 0; i < sizex; i++) np->input[i] = malloc(sizey * sizeof(int));
	for (int i = 0; i < sizex; i++)
		for (int j = 0; j < sizey; j++)
			np->input[i][j] = inp[i][j];
	return np;
}

double neuron_activate (Neuron neuron, double * i, double * w, size_t size)
{
	double sum = 0;
	for (int j = 0; j < size; j++)
		sum += i[j] * w[j];
	return pow(1 + exp(- sum), -1);
}

double neuron_derivativate (Neuron neuron, double out)
{
	return out * (1 - out);
}

double neuron_gradient (Neuron neuron, double error, double dif, double g_sum)
{
	neuron->type == NEURONTYPE_OUTPUT ? error * dif : g_sum * dif;
}
