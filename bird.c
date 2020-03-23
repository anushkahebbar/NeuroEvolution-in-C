#include "bird.h"

void BirdInit(Bird *bird)
{
    bird -> x = 250;
    bird -> y = HEIGHT / 2;
    bird -> w = 50;
    bird -> h = 50;
    bird -> isAlive = 1;
    bird -> gravity = 0.2;
    bird -> velocity = 0;
    bird -> lift = -0.8;
    
	bird -> b.x = bird -> x;
    bird -> b.y = bird -> y;
    bird -> b.w = bird -> w;
    bird -> b.h = bird -> h;
	int NodesArr[3] = {4, 3, 1};
	bird -> nn = newNN(3, NodesArr);
//	DisplayNN(&bird -> nn);
}

void SetBoundary(Bird *bird)
{
    if (bird -> y >= HEIGHT - 45) {
      bird -> y = HEIGHT - 45;
      bird -> velocity = 0;
    }
    if (bird -> y < 0) {
      bird -> y = 0;
      bird -> velocity = 0;
    }
    bird -> b.y = bird -> y;
}
