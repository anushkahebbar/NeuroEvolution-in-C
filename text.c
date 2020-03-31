#include "text.h"

int TextInit(Text *text)
{		
	char str1[] = "Flappy Bird"; 
	strcpy(text -> txt, str1);

	text -> font = TTF_OpenFont("AbyssinicaSIL-R.ttf", 25);
	if(text -> font == NULL) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
		exit(1);
	}

	text -> text_color.r = 255;
	text -> text_color.g = 255;
	text -> text_color.b = 255;
	text -> text_color.a = 255;

	text -> text_speed = 30;
	
	text -> surface = TTF_RenderText_Blended_Wrapped(text -> font, text -> txt, text -> text_color, 640);
    if (text -> surface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
    }
	else{
        text -> text_rect.w = text -> surface -> w;
		text -> text_rect.h = text -> surface -> h;
	}
	text -> text_rect.x = 600;
	text -> text_rect.y = 300;

//	text -> surface = TTF_RenderText_Solid(text -> font, "Flappy Bird", text -> text_color);
//	if(text -> surface == NULL) {
//	    printf("Surface: %s\n", TTF_GetError());
//		exit(1);
//	}
//
//	text -> text_rect.x = 600;
//	text -> text_rect.y = 300;
//	text -> text_rect.w = text -> surface -> w;
//	text -> text_rect.h = text -> surface -> h;
//
	return 1;
}

int UpdateText(Text* t)
{
//	text -> text_rect.x -= text -> text_speed;
	

//Get rid of existing surface
    if (t -> surface != NULL) {
        SDL_FreeSurface(t -> surface);
        t -> surface = NULL;
    }
    t -> surface = TTF_RenderText_Blended_Wrapped(t -> font, t -> txt, t -> text_color, 640);
    if (t -> surface == NULL)
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else {
		t -> text_rect.w = t -> surface -> w;
		t -> text_rect.h = t -> surface -> h;
	}
    //Update width of a surface
    //TTF_SizeText(f, t->mText, &t->mBounds.w, &t->mBounds.h);
    //Update position of a surface
	t -> text_rect.x = 600;
	t -> text_rect.y = 300;

//    t->mBounds.x = SCREEN_WIDTH / 2 - t->mBounds.w / 2;
//    t->mBounds.y = posY;
		
//	text -> surface = TTF_RenderText_Solid(text -> font, str, text -> text_color);

	return 1;
}
