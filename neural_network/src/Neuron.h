#ifndef NEURON_H
#define NEURON_H

#define MEMORYMODE_GET 0
#define MEMORYMODE_SET 1

#define NEURONTYPE_HIDDEN 0
#define NEURONTYPE_OUTPUT 1

typedef MemoryType char;
typedef NeuronType char;

typedef struct {
    NeuronType type;
    double * weights;
    double * inputs;
    size_t size;
    double output;
} Neuron;

struct Neuron * new_neuron ();
double neuron_activate (Neuron neuron, double * i, double * w, size_t size);
double neuron_derivativate (Neuron neuron, double out);
double neuron_gradientor (Neuron neuron, double error, double dif, double g_sum);

#endif
