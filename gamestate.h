#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <stdio.h>

#include "pipe.h"
#include "bird.h"

extern const int WIDTH;
extern const int HEIGHT;
extern int PIPES;
extern int BIRDS;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Bird birds[10];
    Pipe pipes[10];
    int running;
    long long unsigned TimeNow;
    long long unsigned TimeLast;
    unsigned PipeGenerationTimeLast;
    size_t WhichPipeToStart;
} Gamestate;

int InitGame(Gamestate *);
int ReceiveInput(Gamestate *);
int UpdateGame(Gamestate *);
int RenderDisplay(Gamestate *);
void FreeResources(Gamestate *);

#endif  // GAMESTATE_H
