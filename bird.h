#ifndef BIRD_H
#define BIRD_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "nn.h"

extern const int HEIGHT;

typedef struct {
	int x;
	int y;
	int w;
	int h;
	float gravity;
	float velocity;
	float lift;
	int isAlive;
	NeuralNetwork nn;
	SDL_Rect b;

} Bird;


void BirdInit(Bird *);
void SetBoundary(Bird *);

#endif  // BIRD_H
