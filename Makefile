game: main.o gamestate.o bird.o pipe.o nn.o ga.o activation.o
	gcc main.o gamestate.o bird.o pipe.o nn.o ga.o activation.o -o game -lm -lSDL2 -lSDL2main

main.o: main.c main.h
	gcc -c main.c -lSDL2 -lSDL2main

gamestate.o: gamestate.c gamestate.h
	gcc -c gamestate.c -lSDL2 -lSDL2main

bird.o: bird.c bird.h
	gcc -c bird.c -lSDL2 -lSDL2main

pipe.o: pipe.c pipe.h
	gcc -c pipe.c -lSDL2 -lSDL2main

nn.o: nn.c nn.h
	gcc -c nn.c -lm

ga.o: ga.c nn.h
	gcc -c ga.c -lm

activation.o: activation.c activation.h
	gcc -c activation.c -lm

