#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int WIDTH = 1200;
int HEIGHT = 600;
SDL_Texture* load_texture(char*, SDL_Renderer*);

typedef struct {
	TTF_Font *font;
	SDL_Color text_color;
	SDL_Surface *surface;
	SDL_Rect textbox;
	char text_str[100];
	int text_speed;
} Text;

int text_construct(Text*);

SDL_Texture* load_texture(char* path, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
        printf("Unable to load image from surface %s. SDL_image Error: %s\n", path, IMG_GetError());
	else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
            printf("Unable to create texture from surface: %s. SDL_image Error: %s\n", path, IMG_GetError());
        SDL_FreeSurface(surface);
    }
    return texture;
}

int text_construct(Text* text)
{
	text -> font = TTF_OpenFont("graphics/AbyssinicaSIL-R.ttf", 24);
	if (text -> font == NULL) 
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	else {
		char str[100] = "Welcome!";
		strcpy(text -> text_str, str);
		text -> text_color.r = 255;
		text -> text_color.g = 255;
		text -> text_color.b = 255;
		text -> text_color.a = 255;
	    text -> surface = TTF_RenderText_Blended_Wrapped(text -> font, text -> text_str, text -> text_color, 10);
    
		if (text -> surface == NULL) 
    	    printf("Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
		else {
    	    text -> textbox.w = text -> surface -> w;
    	    text -> textbox.h = text -> surface -> h;
 		}
		text -> textbox.x = 600;
		text -> textbox.y = 300;
	}    
	return 1;
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
    	printf("Unable to initialize SDL: %s\n", SDL_GetError());
    	return 1;
	}

	else if (TTF_Init() < 0) {
		printf("Unable to initialise TTF\n");
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Test",     
       			                                                                  SDL_WINDOWPOS_UNDEFINED,  
       			                                                                  SDL_WINDOWPOS_UNDEFINED,  
       			                                                                  WIDTH,
       			                                                                  HEIGHT,                 
       			                                                                  SDL_WINDOW_OPENGL);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |        
	SDL_RENDERER_PRESENTVSYNC);
	
	char path[] = "graphics/fbird.png";
//	SDL_Texture *sprite_texture = load_texture(path, renderer);


	Text *text;
//	char str[] = "Welcome!"; 
	text_construct(text);
//        textUpdate(&e->gameOver, e->mFont, SCREEN_HEIGHT/2);

	

// GAME LOOP ------------------------------------------------------------------
	int running = 1;
	while(running) {
		SDL_Event event;
    	while(SDL_PollEvent(&event)) {
			switch(event.type) {
    	        case SDL_QUIT: ;
					running = 0;
    	        break;
    	        case SDL_WINDOWEVENT_CLOSE:
    	        	if(window) {
    	        	    SDL_DestroyWindow(window);
    	        	    window = NULL;
    	        	}
   		        break;
	         	case SDL_KEYDOWN:
	            	switch(event.key.keysym.sym) {
	            	       case SDLK_ESCAPE: ;;
	            	       break;
	            	}
	        }
	    }
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    SDL_RenderClear(renderer);
//
//		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text -> surface);
//            if (textTexture == NULL)
//                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
//            else {
//                SDL_RenderCopy(renderer, textTexture, NULL, &text -> textbox);
//				SDL_FreeSurface(surface);                
//				SDL_DestroyTexture(textTexture);
//            }	
		
		 SDL_RenderPresent(renderer);
	}
//--------------------------------------------------------------------------------------


// DESTROY RESOURCES-------------------------------------------------
    // Deallocate textures
//    SDL_DestroyTexture(textTexture);
//    textTexture = NULL;
    //Deallocate renderer
    SDL_DestroyRenderer(renderer);
	renderer = NULL;
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    //Deallocate font
    TTF_CloseFont(text -> font);
    text -> font = NULL;
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
	return 0;
}
