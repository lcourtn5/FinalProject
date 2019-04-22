#OBJS specifies which files to compile as part of the project
OBJS = game.cpp window.h

game: game.o
	g++ game.o -w -std=gnu++11 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o game

game.o : $(OBJS)
		g++ -c $(OBJS) -w -std=gnu++11 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

clean:
	rm game.o game
