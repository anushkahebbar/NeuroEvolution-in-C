game: main.o gamestate.o bird.o pipe.o nn.o ga.o activation.o text.o
	gcc main.o gamestate.o bird.o pipe.o nn.o ga.o activation.o text.o -o game -lm -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

main.o: main.c main.h
	gcc -c main.c -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

gamestate.o: gamestate.c gamestate.h
	gcc -c gamestate.c -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

bird.o: bird.c bird.h
	gcc -c bird.c -lSDL2 -lSDL2main

pipe.o: pipe.c pipe.h
	gcc -c pipe.c -lSDL2 -lSDL2main

text.o: text.c text.h 
	gcc -c text.c -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

nn.o: nn.c nn.h
	gcc -c nn.c -lm

ga.o: ga.c nn.h
	gcc -c ga.c -lm

activation.o: activation.c activation.h
	gcc -c activation.c -lm

