#OBJS specifies which files to compile as part of the project
#Initalize when doing more stuff

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
CFLAGS ?= -Wall -Wextra -std=c++17 -Isrc

#LINKER_FLAGS specifies the libraries we're linking against
LFLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
#This is the target that compiles our executable
# add these later

bSDL: obj/bWindow.o obj/bEvent.o

Tests: EventTest WindowTest

clean: 
	rm -f a.out bin/*
	rm -f a.out obj/*
	rm -f a.out tests/obj/*
	rm -f a.out tests/bin/*

EventTest: tests/obj/eventTest.o obj/bWindow.o obj/bEvent.o
	$(CC) tests/obj/eventTest.o obj/bWindow.o obj/bEvent.o $(CFLAGS) $(LFLAGS) -o tests/bin/eventTest

WindowTest: tests/obj/windowTest.o obj/bWindow.o
	$(CC) tests/obj/windowTest.o obj/bWindow.o $(CFLAGS) $(LFLAGS) -o tests/bin/windowTest

tests/obj/eventTest.o: tests/src/eventTest.cpp
	$(CC) -c tests/src/eventTest.cpp $(CFLAGS) $(LFLAGS) -o tests/obj/eventTest.o

tests/obj/windowTest.o: tests/src/windowTest.cpp src/bWindow.h
	$(CC) -c tests/src/windowTest.cpp $(CFLAGS) $(LFLAGS) -o tests/obj/windowTest.o

obj/bWindow.o: src/bWindow.cpp src/bWindow.h
	$(CC) -c src/bWindow.cpp $(CFLAGS) $(LFLAGS) -o obj/bWindow.o

obj/bEvent.o: src/bEvent.cpp src/bEvent.h
	$(CC) -c src/bEvent.cpp $(CFLAGS) $(LFLAGS) -o obj/bEvent.o
