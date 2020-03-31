#include "main.h"

int main(int argc, char* argv[])
{
	Gamestate game;
    if (!InitGame(&game)) printf ("Initialisation failed.\n");
	
	while(game.running) {
		if (!ReceiveInput(&game)) printf("Receiving input failed.\n");
		if (!UpdateGame(&game)) printf("Game updation failed.\n");
		if (!RenderDisplay(&game)) printf("Display rendering failed.\n");
	}   

    FreeResources(&game);
    return 0;
}

            
