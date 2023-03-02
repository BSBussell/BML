#Directories
OBJDIR = obj
TESTOBJDIR = tests/obj
TESTBINDIR = tests/bin

#CC specifies which compiler we're using
CC = g++

BMLsrc = $(wildcard src/*.cpp)

BMLobj := $(notdir $(BMLsrc))
BMLobj := $(addprefix $(OBJDIR)/, $(BMLobj))
BMLobj := $(BMLobj:.cpp=.o)
		 
testsrc = $(wildcard tests/src/*.cpp)

testobj := $(notdir $(testsrc))
testobj := $(addprefix $(TESTOBJDIR)/, $(testobj))
testobj := $(testobj:.cpp=.o)

testbin := $(notdir $(testsrc))
testbin := $(addprefix $(TESTBINDIR)/, $(testbin))
testbin := $(testbin:.cpp=)

#CFLAGS specifies the additional compilation options we're using
CFLAGS := -Wall -Wextra -std=c++17

#IFLAGS specifies which directory to check for include
IFLAGS := -Iinc 

#LFLAGS specify the libraries we're linking against
LFLAGS  := -lSDL2 -lSDL2_image -lSDL2_mixer -lBML

#WFLAGS specifies that we know what we are doing with ar
WFLAGS := -no_warning_for_no_symbols



# If Windows (BOOOOOO)
ifdef OS
    
    RM = del /Q
    FixPath = $(subst /,\,$1)

    disp := echo
    
    bold := THIS LOOKS LIKE SHIT BECAUSE YOU USE WINDOWS
    sgr0 := Loser

    # AHHH I HATE WINDOWS
    # WHAT DO I HAVE TO LIKE INCLUDE THESE IN THE REPO NOW?!
    LFLAGS := -LC:\Development\sdks\i686-w64-mingw32\lib -LC:\Users\benja\Documents\GitHub\BML\bin\libBML.a
    IFLAGS := -IC:\Development\sdks\i686-w64-mingw32\include -IC:\Users\benja\Documents\GitHub\BML\inc

    EXT := .lib

# If Unix (YAAYYYY!!!)
else
	
	disp := @printf

	# Bold Text Variables
	bold := $(shell tput bold)
 	sgr0 := $(shell tput sgr0)

 	EXT := .a
    
    ifeq ($(shell uname), Darwin)
		
		LPATH = /usr/local/lib
 		HEADERPATH = /usr/local/include/BML/
 		
	else
		
		LPATH = /usr/lib
		HEADERPATH = /usr/include/BML/
		
	endif	
endif 


#all rule for just compiling everything
.PHONY: all
all: BML build Tests
	

.PHONY: BML
BML: $(BMLobj)

#Tests for only compiling tests
.PHONY: Tests
Tests: BML build install $(testbin)

.PHONY: build
build: $(BMLobj)
	$(disp) "$(testbin)"
	$(disp) "\n$(bold)----------Building BML LIB File----------------$(sgr0)\n"
	ar rc bin/libBML$(EXT) $(BMLobj)
	ranlib bin/libBML$(EXT) 

.PHONY: install
install: build
	@printf "\n$(bold)----------INSTALLING LIBRARY TO DIRECTORY-------$(sgr0)\n"
	sudo install -m 644 bin/libBML$(EXT) $(LPATH)
	@printf "\n$(bold)--------------PLACING HEADER FILES--------------$(sgr0)\n"
	sudo cp -rf inc/* $(HEADERPATH)

ValgrindTest: Tests
	valgrind --track-origins=yes --suppressions=window.supp --leak-check=full --show-leak-kinds=all ./tests/bin/AnimationTest

# Rules for Building Tests Binary
tests/bin/%: $(testobj)

	$(disp) "\n$(bold)----------COMPILING TEST FILE: $(notdir $@)----------$(sgr0)\n"
	$(CC) tests/obj/$(notdir $@).o $(CFLAGS) $(LFLAGS) -o $@

# Rules for BML obj files
$(OBJDIR)/%.o: src/%.cpp
	$(disp) "\n$(bold)----------COMPILING BML OBJ FILE: $(notdir $@)----------$(sgr0)\n"
	$(CC) $^ $(CFLAGS) $(IFLAGS) -c -o $@ 

# Rules for test obj files
$(TESTOBJDIR)/%.o: tests/src/%.cpp
	$(disp) "\n$(bold)----------COMPILING TEST OBJ FILE: $(notdir $@)----------$(sgr0)\n"
	$(CC) $^ $(CFLAGS) $(IFLAGS) -c -o $@ 

.PHONY: clean
clean: 
	@printf "\n$(bold)----------REMOVING PREVIOUS BUILDS----------$(sgr0)\n"
	rm -f $(BMLobj) 
	rm -f $(testobj)
	rm -f bin/*
	rm -f a.out tests/bin/*
