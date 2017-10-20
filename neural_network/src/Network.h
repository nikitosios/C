#ifndef NETWORK_H
#define NETWORK_H

#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"

#define THRESHOLD 0.001

typedef struct {
	InputLayer * inputLayer;
	HiddenLayer * hiddenLayer;
	OutputLayer * outputLayer;
	double * fact;
} Network;

Network * new_Network (void);
void train (Network * net);
void test (Network * net);
double getMSE (double * errors, size_t length);
double getCost (double * mses, size_t length);

#endif
