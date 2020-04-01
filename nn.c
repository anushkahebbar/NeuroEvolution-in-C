#include "nn.h"

int get_wm_size(int Layers, int NodesArr[])
{
  int size = 0;
  for(int i = 0; i < Layers - 1; ++i)

  size += (NodesArr[i] * NodesArr[i + 1]);
  return size;
}

int get_bm_size(int Layers, int NodesArr[])
{
  int size = 0;
  for(int i = 1; i < Layers; ++i)
    size += NodesArr[i];
  return size;
}

float WeightedSum(float *weights, float *bias, float inputs[], int nodes)
{
  float sum = *bias;
  for (int i = 0; i < nodes; ++i) {
    sum += weights[i] * inputs[i];
  }
  return sum;
}

float* FeedForward(NeuralNetwork *nn, float InputArr[])
{
  int *NodesArr = (nn -> NodesArr);
  int Layers = (nn -> Layers);

  for (int i = 0; i < Layers - 1; ++i) {
    int prev_layer = NodesArr[i];
    int curr_layer = NodesArr[i + 1];

    float *layer_activ = (float*) malloc(curr_layer * sizeof(float));

    for (int j = 0; j < curr_layer; ++j) {
      float *weight_arr = ((nn -> Weights) + (i*curr_layer) + (j*prev_layer*curr_layer));
      float *bias_arr = ((nn -> Biases) + (i*curr_layer) + j);
      layer_activ[j] = swish(WeightedSum(weight_arr, bias_arr, InputArr, prev_layer));
    }
    InputArr = layer_activ;
  }
  return InputArr;
}


NeuralNetwork newNN(int Layers, int NodesArr[])
{
	float rand_val = 2.0;
	int wm_size = get_wm_size(Layers, NodesArr);
	int bm_size = get_bm_size(Layers, NodesArr);

	NeuralNetwork* nn = malloc(sizeof(NeuralNetwork));
	
	nn -> NodesArr = NodesArr;
	nn -> Layers = Layers;
	nn -> Weights = malloc(wm_size*sizeof(float));
	nn -> Biases = malloc(bm_size*sizeof(float));
	BirdInit(&nn -> bird);
	
	int a = 2;
	for(int i = 0; i < (Layers - 1); ++i) {
	int curr_layer = NodesArr[i + 1];
    int prev_layer = NodesArr[i];

	    for(int j = 0; j < curr_layer; ++j) {
			float b_val = (float)((double)rand()/(double)(RAND_MAX/a));
			((nn -> Biases) + (i*curr_layer))[j] = b_val;
	
			for(int k = 0; k < prev_layer; ++k) {
		        float w_val = (float)((double)rand()/(double)(RAND_MAX/a));
		        ((nn -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k] = w_val;
			}
		}
	}
	return *nn;
}

void DisplayNN(NeuralNetwork *nn)
{
  printf("Weights:\n");
  for(int i = 0; i < nn -> Layers - 1; ++i) {
    int curr_layer = nn -> NodesArr[i + 1];
    int prev_layer = nn -> NodesArr[i];

    for(int j = 0; j < curr_layer; ++j) {
      for(int k = 0; k < prev_layer; ++k) {
        printf("%f\t", ((nn -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k]);
      }
      printf("\n");
    }
    printf("\n");
  }
  printf("Biases:\n");
  for(int i = 0; i < nn -> Layers - 1; ++i) {
    int curr_layer = nn -> NodesArr[i + 1];
    int prev_layer = nn -> NodesArr[i];
    for(int j = 0; j < curr_layer; ++j) {
      printf("%f\t", ((nn -> Biases) + (i*curr_layer))[j]);
    }
    printf("\n");
  }
  printf("\n\n");
}

