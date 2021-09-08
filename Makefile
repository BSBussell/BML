#OBJS specifies which files to compile as part of the project
#Initalize when doing more stuff

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
CFLAGS ?= -Wall -Wextra -std=c++17 -Isrc

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
#This is the target that compiles our executable
# add these later

all: objects build Tests

objects: bWindow bEvent

Tests: SoundTest TextureTest EventTest WindowTest

clean: 
	rm -f a.out bin/*
	rm -f a.out obj/*
	rm -f a.out tests/obj/*
	rm -f a.out tests/bin/*

build: bWindow bEvent bSound
	ar rc bin/bSDL.a obj/*.o
	ranlib bin/bSDL.a

SoundTest: soundTest.o bSound bWindow bEvent
	$(CC) tests/obj/soundTest.o obj/bSound.o obj/bWindow.o obj/bEvent.o $(CFLAGS) $(LFLAGS) -o tests/bin/soundTest

TextureTest: textureTest.o bWindow bEvent
	$(CC) tests/obj/textureTest.o obj/bWindow.o obj/bEvent.o $(CFLAGS) $(LFLAGS) -o tests/bin/textureTest

EventTest: eventTest.o bWindow bEvent
	$(CC) tests/obj/eventTest.o obj/bWindow.o obj/bEvent.o $(CFLAGS) $(LFLAGS) -o tests/bin/eventTest

WindowTest: windowTest.o bWindow
	$(CC) tests/obj/windowTest.o obj/bWindow.o $(CFLAGS) $(LFLAGS) -o tests/bin/windowTest

soundTest.o: tests/src/soundTest.cpp
	$(CC) -c tests/src/soundTest.cpp $(CFLAGS) -o tests/obj/soundTest.o

textureTest.o: tests/src/textureTest.cpp
	$(CC) -c tests/src/textureTest.cpp $(CFLAGS) -o tests/obj/textureTest.o

eventTest.o: tests/src/eventTest.cpp
	$(CC) -c tests/src/eventTest.cpp $(CFLAGS) -o tests/obj/eventTest.o

windowTest.o: tests/src/windowTest.cpp src/bWindow/bWindow.h
	$(CC) -c tests/src/windowTest.cpp $(CFLAGS) -o tests/obj/windowTest.o

bSound: src/bSound/bSound.cpp src/bSound/bSound.h
	$(CC) -c src/bSound/bSound.cpp $(CFLAGS) -o obj/bSound.o

bWindow: src/bWindow/bWindow.cpp src/bWindow/bWindow.h
	$(CC) -c src/bWindow/bWindow.cpp $(CFLAGS) -o obj/bWindow.o

bEvent: src/bEvent/bEvent.cpp src/bEvent/bEvent.h
	$(CC) -c src/bEvent/bEvent.cpp $(CFLAGS) -o obj/bEvent.o
