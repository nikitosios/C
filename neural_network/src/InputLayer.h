#ifndef INPUTLAYER_H
#define INPUTLAYER_H

typedef struct {
	double * a1;
	double * a2;
} Tuple;

typedef struct {
	Tuple ** trainset;
    size_t trainsetLength;
} InputLayer;

InputLayer * new_InputLayer (void);

#endif
