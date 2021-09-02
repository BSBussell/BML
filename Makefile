#OBJS specifies which files to compile as part of the project
OBJS = tests/windowTest.cpp src/bWindow.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
CFLAGS ?= -Wall -Wextra -std=c++11 -Isrc

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin/windowTest.o
#This is the target that compiles our executable
all : $(OBJ_NAME)

clean: 
	rm -f a.out bin/*

bin/windowTest.o: tests/windowTest.cpp
	$(CC) $(OBJS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
