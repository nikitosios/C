#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_h

#include "Neuron.h"
#include "Layer.h"
#include "OutputLayer.h"
#include "Network.h"

void outputLayer_recognize (Layer * layer, Network * net, Layer nextLayer)
{
	for (int i = 0; i < layer->numofneurons; i++)
		net->fact[i] = layer->neurons[i]->output;
}

double * outputLayer_backwardPass (Layer * layer, double * errors)
{
	double * gr_sum = malloc(layer->numofprevneurons * sizeof(double));
	for (int i = 0; i < layer->numofprevneurons; i++)
	{
		double sum = 0;
		for (int j = 0; j < layer->numofprevneurons; j++)
			sum += layer->neurons[j]->weights[i] * neuron_gradientor(layer->neurons[j],
					errors[j], neuron_derivativator(layer->neurons[j], layer->neurons[j]->output), 0);
		gr_sum[j] = sum;
	}
	for (int i = 0; i < layer->numofneurons; i++)
		for (int j = 0; j < layer->numofprevneurons; j++)
			layer->neurons[i]->weights[n] += LEARNINGRATE * layer->neurons[i]->inputs[j] *
				neuron_gradientor(layer->neurons[i], errors[i], neuron_derivativator(layer->neurons[i],
							layer->neurons[i]->output), 0);
	return gr_sum;
}

#endif
