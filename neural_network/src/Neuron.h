#ifndef NEURON_H
#define NEURON_H

#define MEMORYMODE_GET 0
#define MEMORYMODE_SET 1

#define NEURONTYPE_HIDDEN 0
#define NEURONTYPE_OUTPUT 1

#define LEARNINGRATE 0.1

typedef char MemoryMode;
typedef char NeuronType;

typedef struct {
    NeuronType type;
    double * weights;
    double * inputs;
    size_t size;
    double output;
} Neuron;

typedef struct {
    int numofneurons;
    int numofprevneurons;
    double * data;
    Neuron ** neurons;
} Layer;

Neuron * new_Neuron (double * inputs, double * weights, size_t size, NeuronType type);
double neuron_activate (Neuron * neuron, double * i, double * w, size_t size);
double neuron_derivativate (Neuron * neuron, double out);
double neuron_gradientor (Neuron * neuron, double error, double dif, double g_sum);

Layer * new_Layer (int non, int nopn, NeuronType nt);
void layer_setData (Layer * layer, double * data);
double ** layer_weightInitialize (Layer * layer, MemoryMode mm, NeuronType nt);

#endif
