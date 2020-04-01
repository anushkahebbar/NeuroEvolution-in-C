#include "gamestate.h"

const int WIDTH = 1200;
const int HEIGHT = 600;
int PIPES = 4;
int BIRDS = 5;
float THRESHOLD = 20;
int ACTIVE = 0;

int InitGame(Gamestate *game)
{
    game -> running = 1;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
      printf("Unable to initialize SDL: %s\n", SDL_GetError());
      return 0;
    }
	if (TTF_Init() == -1) {
		printf("Unable to initialise TTF\n");
		return 0;
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
      
//		TextInit(game -> text);

		int NodesArr[3] = {4, 3, 1};

		for (int i = 0; i < PIPES; ++i) 
			PipeInit(&game -> pipes[i], i + 1); 
		for(int j = 0; j < BIRDS; ++j) {	            
			game -> nn[j] = newNN(3, NodesArr);
			DisplayNN(&game -> nn[j]);
		}
    }
    return 1;
}

int ReceiveInput(Gamestate *game)
{
	SDL_Event event;
    while(SDL_PollEvent(&event)) {
		switch(event.type) {
            case SDL_QUIT: ;
				game -> running = 0;
            break;
            case SDL_WINDOWEVENT_CLOSE: ;
           		if(game -> window) {
          	      SDL_DestroyWindow(game -> window);
          	      game -> window = NULL;
          	      game -> running = 0;
          		}
            break;
            case SDL_KEYDOWN:;
            	switch(event.key.keysym.sym)
           		{
                	case SDLK_ESCAPE: ;				                       
						game -> running  = 0;
                   break;
            	}
        }
    }
	return 1;
}

int UpdateBird(Pipe* pipe, NeuralNetwork* nn)
{
	float inputs[4];
	inputs[0] = nn -> bird.b.y;
	inputs[1] = ((pipe -> x) - (nn -> bird.b.x));
	inputs[2] = pipe -> top.y;
	inputs[3] = pipe -> bot.y;

	float* output = FeedForward(nn, inputs);
//	printf("NN Output: %f\n", *output);

	if (*output > THRESHOLD)
		nn -> bird.velocity += nn -> bird.lift;
	nn -> bird.velocity += nn -> bird.gravity;
	nn -> bird.y += nn -> bird.velocity; 
	nn -> bird.b.y = nn -> bird.y;
	return 1;
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
	
//	UpdateText(game -> text);

    for (int i = 0; i < PIPES; ++i)
		UpdatePipe(&game -> pipes[i], deltaTime, i + 1);
	for(int j = 0; j < BIRDS; ++j)
        SetBoundary(&game -> nn[j].bird);

    for (int i = 0; i < PIPES; ++i)
        for(int j = 0; j < BIRDS; ++j) {
			if (game -> pipes[i].isActive && (game -> pipes[i].x + game -> pipes[i].width) >= game -> nn[j].bird.x) {
				UpdateBird(&game -> pipes[i], &game -> nn[j]);
				printf("Updated NN %d\n", j + 1);
			}
            if (CheckCollision(&game -> pipes[i], &game -> nn[j].bird))
                game -> nn[j].bird.isAlive = 0;
		}
	return 1;
}

int RenderDisplay(Gamestate *game)
{
    SDL_SetRenderDrawColor(game -> renderer, 0, 0, 0, 255);
    SDL_RenderClear(game -> renderer);
    
//	if (ACTIVE == 0) {

//		game -> text -> texture = SDL_CreateTextureFromSurface(game -> renderer, game -> text -> surface);			
//
//		if (game -> text -> texture == NULL) {
//                printf("Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError());
//				exit(1);
//		}
//		else {
//			SDL_RenderCopy(game -> renderer, game -> text -> texture, NULL, &game -> text -> text_rect);
//			SDL_DestroyTexture(game -> text -> texture);
//			game -> text -> texture = NULL;
//		}
//	}
		
    SDL_SetRenderDrawColor(game -> renderer, 255, 255, 255, 255);
    for (int i = 0; i < PIPES; ++i) {
        if (game -> pipes[i].isActive) {
			if (ACTIVE == 0) ACTIVE = 1;
//			printf("---------------\n%d\n-----------------", i);
            SDL_RenderFillRect(game -> renderer, &game -> pipes[i].top);
            SDL_RenderFillRect(game -> renderer, &game -> pipes[i].bot);
        }
    }
    
    for (int j = 0; j < BIRDS; ++j) {
        if (game -> nn[j].bird.isAlive) {
            SDL_RenderDrawRect(game -> renderer, &game -> nn[j].bird.b);
//			SDL_SetRenderDrawColor(game -> renderer, 211, 211, 211, 0.05);
//			SDL_RenderFillRect(game -> renderer, &game -> nn[j].bird.b);
        }
		else {
			SDL_SetRenderDrawColor(game -> renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(game -> renderer, &game -> nn[j].bird.b);
//			SDL_SetRenderDrawColor(game -> renderer, 255, 0, 0, 0.2);
//			SDL_RenderFillRect(game -> renderer, &game -> nn[j].bird.b);
		}
    }
    
    SDL_RenderPresent(game -> renderer);
	return 1;
}

void FreeResources(Gamestate *game)
{
    SDL_DestroyRenderer(game -> renderer);
    SDL_DestroyWindow(game -> window);
	SDL_FreeSurface(game -> text -> surface);
	TTF_CloseFont(game -> text -> font);
    SDL_Quit();
	TTF_Quit();
}
