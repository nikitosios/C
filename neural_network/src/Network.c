#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Network.h"

#define NUMOFINPUTS 1920 * 1080 * 3

Network * new_Network (void)
{
	Network * network;
	network = malloc(sizeof(Network));
	
	network->inputLayer = new_inputLayer();
	nwtwork->hiddenLayer = new_Layer(NUMOFINPUTS, NUMOFINPUTS / 3, NEURONTYPE_HIDDEN);
	network->outputLayer = new_Layer(33, 1920 * 1080 *, NEURONTYPE_OUTPUT);
	network->factLength = 33;
	network->fact = malloc(network->factLength * sizeof(double));

	return network;
}

double getMSE (double * errors, size_t length)
{
	double sum = 0;
	for (size_t i = 0; i < length; i++)
		sum += pow(errors[i], 2);
	return 0.5 * sum;
}

double getCost (double * mses, size_t length)
{
	double sum = 0;
	for (int i = 0; i < length; i++)
		sum += mses[i];
	return (sum / (double) length);
}

void train (Network * net)
{
	double * temp_mses = malloc(net->inputLayer->trainsetLength * sizeof(double));
	double temp_cost = 0;
	do
	{
		for (int i = 0; i < net->inputLayer->trainsetLength; i++)
		{
			hiddenLayer_setData(net->hiddenLayer, net->inputLayer->trainset[i].a1);
			hiddenLayer_recognize(net->hiddenLayer, NULL, net->outputLayer);
			outputLayer_recognize(net->outputLayer, net, NULL);
			double * errors = malloc(NUMOFINPUTS * sizeof(double));
			for (int j = 0; j < NUMOFINPUTS; j++)
				errors[j] = net->inputLayer->trainset[i]->a2 - net->fact[j];
			temp_mses[i] = getMSE(errors, NUMOFINPUTS);
			double * temp_gsums = outputLayer_backwardPass(net->outputLayer, errors, NUMOFINPUTS);
			hiddenLayer_backwardPass(net->hiddenLayer, temp_gsums);
		}
		temp_cost = getCost(temp_mses);
		printf("%f\n", temp_cost);
	} while (temp_cost > threshold);
	layer_weightInitialize(net->hiddenLayer, MEMORYMODE_SET, NEURONTYPE_HIDDEN);
	layer_weightInitialize(net->outputLayer, MEMORYMODE_SET, NEURONTYPE_OUTPUT);
}

void test (Network * net)
{
	for (int i = 0; i < net->inputLayer->trainSetLength; i++)
	{
		hiddenLayer_setData(net->hiddenLayer, net->inputLayer->trainset[i]->a1);
		hiddenLayer_recognize(net->hiddenLayer, NULL, net->outputLayer);
		outputLayer_recognize(net->outputLayer, net, NULL);
		for (int j = 0; j < net->factLength; j++)
			printf("%f\n", net->fact[j]);
		printf("\n");
	}
}
