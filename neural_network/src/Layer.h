#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include "InputLayer.h"

typedef struct {
    int numofneurons;
    int numofprevneurons;
    double * data;
    Neuron ** neurons;
} Layer;

typedef Layer HiddenLayer;
typedef Layer OutputLayer;

typedef struct {
	InputLayer * inputLayer;
	HiddenLayer * hiddenLayer;
	OutputLayer * outputLayer;
	double * fact;
    size_t factLength;
} Network;

Layer * new_Layer (int non, int nopn, NeuronType nt);
void layer_setData (Layer * layer, double * data);
double ** layer_weightInitialize (Layer * layer, MemoryMode mm, NeuronType nt);

#endif
