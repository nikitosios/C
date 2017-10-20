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

Neuron * new_Neuron (double * inputs, double * weights, size_t size, NeuronType type);
double neuron_activator (Neuron * neuron, double * i, double * w, size_t size);
double neuron_derivativator (Neuron * neuron, double out);
double neuron_gradientor (Neuron * neuron, double error, double dif, double g_sum);

#endif
