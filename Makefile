#OBJS specifies which files to compile as part of the project
OBJS = tests/windowTest.cpp src/bWindow.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
CFLAGS ?= -Wall -Wextra -std=c++11 -Isrc

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bin/windowTest.o
#This is the target that compiles our executable

bSDL: obj/bWindow.o

clean: 
	rm -f a.out bin/*
	rm -f a.out obj/*
	rm -f a.out tests/obj/*
	rm -f a.out tests/bin/*

WindowTest: tests/obj/windowTest.o obj/bWindow.o
	$(CC) tests/obj/windowTest.o obj/bWindow.o $(CFLAGS) $(LFLAGS) -o tests/bin/windowTest

tests/obj/windowTest.o: tests/windowTest.cpp src/bWindow.h
	$(CC) -c tests/windowTest.cpp $(CFLAGS) $(LFLAGS) -o tests/obj/windowTest.o

obj/bWindow.o: src/bWindow.cpp src/bWindow.h
	$(CC) -c src/bWindow.cpp $(CFLAGS) $(LFLAGS) -o obj/bWindow.o
