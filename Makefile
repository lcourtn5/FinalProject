#OBJS specifies which files to compile as part of the project
OBJS = game.cpp window.h

game: game.o
	g++ game.o -w -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o game

game.o : $(OBJS)
		g++ -c $(OBJS) -w -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
