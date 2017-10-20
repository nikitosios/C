#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"

typedef struct {
    int numofneurons;
    int numofprevneurons;
    double * data;
    Neuron ** neurons;
} Layer;

Layer * new_Layer (int non, int nopn, NeuronType nt);
void layer_setData (Layer * layer, double * data);
double ** layer_weightInitialize (Layer * layer, MemoryMode mm, NeuronType nt);

#endif
