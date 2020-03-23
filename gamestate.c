#include "gamestate.h"

const int WIDTH = 1200;
const int HEIGHT = 600;
int PIPES = 4;
int BIRDS =1;

int InitGame(Gamestate *game)
{
    game -> running = 1;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
      printf("Unable to initialize SDL: %s\n", SDL_GetError());
      return 1;
    }
    else {
        game -> window = SDL_CreateWindow("Flappy Bird with a Twist",                  // window title
                                                                          SDL_WINDOWPOS_UNDEFINED,  // initial x position
                                                                          SDL_WINDOWPOS_UNDEFINED,  // initial y position
                                                                          WIDTH,
                                                                          HEIGHT,                 
                                                                          SDL_WINDOW_OPENGL);               // flags    

        game -> renderer = SDL_CreateRenderer(game -> window, -1, SDL_RENDERER_ACCELERATED |        
SDL_RENDERER_PRESENTVSYNC);

        game -> TimeLast = 0;
        game-> TimeNow = SDL_GetPerformanceCounter();
        game-> WhichPipeToStart = 0;
        game-> PipeGenerationTimeLast = 0;   
      
		for (int i = 0; i < PIPES; ++i) 
			PipeInit(&game -> pipes[i]); 
		for(int j = 0; j < BIRDS; ++j)	            
			BirdInit(&game -> birds[j]);
    }
    return 0;
}

int ReceiveInput(Gamestate *game)
{
	SDL_Event event;
    while(SDL_PollEvent(&event)) {
		switch(event.type) {
            case SDL_QUIT: ;
				game -> running = 0;
            break;
            case SDL_WINDOWEVENT_CLOSE:
            if(game -> window) {
                SDL_DestroyWindow(game -> window);
                game -> window = NULL;
                game -> running = 0;
            }
            break;
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
           {
                   case SDLK_ESCAPE: ;
						FreeResources(game);				                       
						game -> running  = 0;
                   break;
            }
        }
    }
	return 0;
}

int UpdateGame(Gamestate *game)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
       
    game -> TimeLast = game -> TimeNow;
    game -> TimeNow = SDL_GetPerformanceCounter();
    double deltaTime = ((game -> TimeNow - game -> TimeLast) * 1000 / (double) SDL_GetPerformanceFrequency()) / 1000;
    unsigned currentTime = SDL_GetTicks();
//	printf("%u\n", currentTime);
        
    if (game -> WhichPipeToStart < PIPES && currentTime > game -> PipeGenerationTimeLast + 4000) {
        if (game -> pipes[game -> WhichPipeToStart].isActive == 0) {
//			printf("------------------------\n%lu\n-----------------------\n", game -> WhichPipeToStart);
            game -> pipes[game -> WhichPipeToStart].isActive = 1;
            game -> WhichPipeToStart++;
            game -> PipeGenerationTimeLast = currentTime;
        }
        game -> WhichPipeToStart %= PIPES;
    }

    for (int i = 0; i < PIPES; ++i)
		UpdatePipe(&game -> pipes[i], deltaTime);
	for(int j = 0; j < BIRDS; ++j)
        SetBoundary(&game -> birds[j]);

    for (int i = 0; i < PIPES; ++i)
        for(int j = 0; j < BIRDS; ++j) {
			UpdateBird(&game -> pipes[i], &game -> birds[j]);
            if (CheckCollision(&game -> pipes[i], &game -> birds[j]))
                game -> birds[j].isAlive = 0;
		}
	return 0;
}

int RenderDisplay(Gamestate *game)
{
    SDL_SetRenderDrawColor(game -> renderer, 0, 0, 0, 255);
    SDL_RenderClear(game -> renderer);
    
    SDL_SetRenderDrawColor(game -> renderer, 255, 255, 255, 255);
    for (int i = 0; i < PIPES; ++i) {
        if (game -> pipes[i].isActive) {
//			printf("---------------\n%d\n-----------------", i);
            SDL_RenderFillRect(game -> renderer, &game -> pipes[i].top);
            SDL_RenderFillRect(game -> renderer, &game -> pipes[i].bot);
        }
    }
    
    for (int j = 0; j < BIRDS; ++j) {
        if (game -> birds[j].isAlive) {
            SDL_RenderFillRect(game -> renderer, &game -> birds[j].b);
        }
//		else {
//			SDL_SetRenderDrawColor(game -> renderer, 255, 0, 0, 255);
//			SDL_RenderFillRect(game -> renderer, &game -> birds[j].b);
//		}
    }
    
    SDL_RenderPresent(game -> renderer);
	return 0;
}

void FreeResources(Gamestate *game)
{
    SDL_DestroyRenderer(game -> renderer);
    SDL_DestroyWindow(game -> window);
    SDL_Quit();
}
