#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "nn.h"
#include "pipe.h"
#include "bird.h"
#include "text.h"

extern const int WIDTH;
extern const int HEIGHT;
extern int PIPES;
extern int BIRDS;
extern int ACTIVE;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
	Text *text;
    NeuralNetwork nn[10];
    Pipe pipes[4];
    int running;
    long long unsigned TimeNow;
    long long unsigned TimeLast;
    unsigned PipeGenerationTimeLast;
    size_t WhichPipeToStart;
} Gamestate;

int InitGame(Gamestate *);
int ReceiveInput(Gamestate *);
int UpdateBird(Pipe *, NeuralNetwork *);
int UpdateGame(Gamestate *);
int RenderDisplay(Gamestate *);
void FreeResources(Gamestate *);

#endif  // GAMESTATE_H
