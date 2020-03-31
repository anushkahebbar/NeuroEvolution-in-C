#ifndef NN_H
#define NN_H

#include "activation.h"
#include "bird.h"

typedef struct NeuralNetwork {

	int *NodesArr;
	int Layers;
	float *Weights;
	float *Biases;
	Bird bird;

} NeuralNetwork;

int get_wm_size(int, int []);
int get_bm_size(int, int []);
float WeightedSum(float *, float *, float [], int);
float* FeedForward(NeuralNetwork *, float []);
NeuralNetwork newNN(int, int []);
void DisplayNN(NeuralNetwork *);

NeuralNetwork* Clone(NeuralNetwork *);
NeuralNetwork* Crossover(NeuralNetwork *, NeuralNetwork *);
float* Mutate(NeuralNetwork *, float);


#endif 	// NN_H

