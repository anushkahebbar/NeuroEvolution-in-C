#include "nn.h"


NeuralNetwork* Clone(NeuralNetwork *nn)
{
  NeuralNetwork *nn_clone = malloc(sizeof(NeuralNetwork));
  nn_clone -> NodesArr = nn -> NodesArr;
  nn_clone -> Layers = nn -> Layers;
  int *NodesArr = nn_clone -> NodesArr;
  int Layers = nn_clone -> Layers;

  int wm_size = get_wm_size(Layers, NodesArr);
  int bm_size = get_bm_size(Layers, NodesArr);

  nn_clone -> Weights = malloc(wm_size*sizeof(float));
  nn_clone -> Biases = malloc(bm_size*sizeof(float));

  for(int i = 0; i < (Layers - 1); ++i) {
    int curr_layer = NodesArr[i + 1];
    int prev_layer = NodesArr[i];

    for(int j = 0; j < curr_layer; ++j) {
      float b_val = ((nn -> Biases) + (i*curr_layer))[j];
      ((nn_clone -> Biases) + (i*curr_layer))[j] = b_val;

      for(int k = 0; k < prev_layer; ++k) {
        float w_val = ((nn -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k];
        ((nn_clone -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k] = w_val;
      }
    }
  }
  return nn_clone;
}


NeuralNetwork* Crossover(NeuralNetwork *parent_1, NeuralNetwork *parent_2)
{
  float b_choose, w_choose, b_val, w_val;

  NeuralNetwork *child = malloc(sizeof(NeuralNetwork));
  child -> NodesArr = parent_1 -> NodesArr;
  child -> Layers = parent_1 -> Layers;
  int *NodesArr = child -> NodesArr;
  int Layers = child -> Layers;

  int wm_size = get_wm_size(Layers, NodesArr);
  int bm_size = get_bm_size(Layers, NodesArr);

  child -> Weights = malloc(wm_size*sizeof(float));
  child -> Biases = malloc(bm_size*sizeof(float));

  for(int i = 0; i < (Layers - 1); ++i) {
    int curr_layer = NodesArr[i + 1];
    int prev_layer = NodesArr[i];

    for(int j = 0; j < curr_layer; ++j) {
      b_choose = ((float)rand()/(float)(RAND_MAX));

      if (b_choose > 0.5) b_val = ((parent_1 -> Biases) + (i*curr_layer))[j];
      else b_val = ((parent_2 -> Biases) + (i*curr_layer))[j];
      ((child -> Biases) + (i*curr_layer))[j] = b_val;

      for(int k = 0; k < prev_layer; ++k) {
        w_choose = ((float)rand()/(float)(RAND_MAX));

        if (w_choose > 0.5) w_val = ((parent_1 -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k];
        else w_val = ((parent_2 -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k];
        ((child -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k] = w_val;
      }
    }
  }
  return child;
}


float* Mutate(NeuralNetwork *nn, float mutate_rate)
{
  float rand_val = 1.0, mutate_brand, mutate_wrand;
  float iter_num = 0.0, num_wmutated = 0.0, num_bmutated = 0.0;
  int *NodesArr = nn -> NodesArr;
  int Layers = nn -> Layers;

  for(int i = 0; i < (Layers - 1); ++i) {
    int curr_layer = NodesArr[i + 1];
    int prev_layer = NodesArr[i];

    for(int j = 0; j < curr_layer; ++j) {
      for(int k = 0; k < prev_layer; ++k) {
        iter_num += 1.0;
        mutate_wrand = (((float)rand()/(float)(RAND_MAX)) * rand_val);
        mutate_brand = (((float)rand()/(float)(RAND_MAX)) * rand_val);

        if(mutate_rate > mutate_wrand) {
          num_wmutated += 1.0;
          float w_val = (((float)rand()/(float)(RAND_MAX)) * rand_val);
          ((nn -> Weights) + (i*curr_layer*prev_layer) + (j*prev_layer))[k] = w_val;
        }
        if(mutate_rate > mutate_brand) {
          num_bmutated += 1.0;
          float b_val = (((float)rand()/(float)(RAND_MAX)) * rand_val);
          ((nn -> Biases) + (i*curr_layer))[j] = b_val;
        }
      }
    }
  }
  float *mutated_frac = malloc(2*sizeof(float));
  mutated_frac[0] = num_bmutated/iter_num;
  mutated_frac[1] = num_wmutated/iter_num;
  return mutated_frac;
}
