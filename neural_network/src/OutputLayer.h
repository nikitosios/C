#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

#include "Layer.h"
#include "Network.h"

typedef Layer OutputLayer;

void outputLayer_recognize (Layer * layer, Network * net, Layer nextLayer);
double * outputLayer_backwardPass (Layer * layer, double * errors);

#endif
