#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include "Neuron.h"
#include "Layer.h"

void hiddenLayer_recognize (Layer * layer, Network * net, Layer * nextLayer);
double * hiddenLayer_backwardPass (Layer * layer, double * gr_sums);

#endif
