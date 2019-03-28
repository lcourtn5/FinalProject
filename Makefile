#OBJS specifies which files to compile as part of the project
OBJS = tutorial.cpp

#OBJ_NAME specifies the name of our executable
OBJ_NAME = tutorial

#This is the target that compiles our executable
all : $(OBJS)
		g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)
