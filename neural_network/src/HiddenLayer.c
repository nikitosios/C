#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Neuron.h"
#include "Layer.h"
#include "HiddenLayer.h"
#include "Network.h"

void hiddenLayer_recognize (Layer * layer, Network * net, Layer * nextLayer)
{
	double * hidden_out = malloc(layer->numofneurons * sizeof(double));
	for (int i = 0; i < layer->numofneurons; i++)
		hidden_out[i] = layer->neurons[i]->output;
	layer_setData(layer, hidden_out);
}

double * hiddenLayer_backwardPass (Layer * layer, double * gr_sums)
{
	double * gr_sum = NULL;
	for (int i = 0; i < layer->numofneurons; i++)
		for (int j = 0; j < layer->numofprevneurons; j++)
			layer->neurons[i]->weights[j] += LEARNINGRATE *
				layer->neurons[i]->inputs[j] * neuron_gradientor(layer->neurons[i], 0,
						neuron_derivativator(layer->neurons[i],
							layer->neurons[i]->output), gr_sums[i]);
	return gr_sum;
}
