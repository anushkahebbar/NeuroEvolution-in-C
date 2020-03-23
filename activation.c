#include "activation.h"

float sigmoid(float X)
{
	return 1 / (1 + expf(-X));
}

float relu(float X)
{
	if (X < 0) return 0;
	else return X / 10;
}

float sigmoid_der(float X)
{
	return sigmoid(X) * (1.0 - sigmoid(X));
}

float relu_der(float X)
{
	if (X < 0) return 0;
	else return 1;
}

float tanh_af(float X)
{
	return tanhf(X);
}

float tanh_der(float X)
{
	return 1 / (pow(coshf(X), 2));
}


