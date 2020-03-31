#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float sigmoid(float);
float relu(float);
float sigmoid_der(float);
float relu_der(float);
float tanh_af(float);
float tanh_der(float);
float swish(float);

#endif 	// ACTIVATION_H
