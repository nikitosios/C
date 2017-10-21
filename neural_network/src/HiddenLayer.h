#ifndef HIDDENLAYER_H
#define HIDDENLAYER_H

#include "Layer.h"
#include "Network.h"

typedef Layer HiddenLayer;

void hiddenLayer_recognize (Layer * layer, Network * net, Layer * nextLayer);
double * hiddenLayer_backwardPass (Layer * layer, double * gr_sums);

#endif
