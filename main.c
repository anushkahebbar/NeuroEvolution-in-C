#include "main.h"

int main(int argc, char* argv[])
{
	Gamestate game;
    if (InitGame(&game)) printf ("Initialisation failed.\n");
    else {
        while(game.running) {
            if (ReceiveInput(&game)) printf("one\n");
            else {
				if (UpdateGame(&game)) printf("two\n");
				else {
		            if (RenderDisplay(&game)) printf("three\n");
				}
			}
		}
	}   
    FreeResources(&game);
    return 0;
}

            
