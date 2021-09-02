#OBJS specifies which files to compile as part of the project
OBJS = tests/windowTest.cpp src/bWindow.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CFLAGS ?= -Wall -Wextra -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin/windowTest
#This is the target that compiles our executable
all : $(OBJ_NAME)

clean: 
	rm -f a.out bin/*

bin/windowTest: tests/windowTest.cpp
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
