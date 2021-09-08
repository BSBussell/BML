#Directories
OBJDIR = obj
TESTOBJDIR = tests/obj

#CC specifies which compiler we're using
CC = g++

bSDLsrc = $(wildcard src/bSDL/*.cpp) \
		 $(wildcard src/bData/*.cpp) \
		 $(wildcard src/bTexture/*.cpp) \
		 $(wildcard src/bWindow/*.cpp) \
		 $(wildcard src/bEvent/*.cpp) \
		 $(wildcard src/bSound/*.cpp)

bSDLobj := $(notdir $(bSDLsrc))
bSDLobj := $(addprefix $(OBJDIR)/, $(bSDLobj))
bSDLobj := $(bSDLobj:.cpp=.o)

		 
testsrc = $(wildcard tests/src/*.cpp)

testobj := $(notdir $(testsrc))
testobj := $(addprefix $(TESTOBJDIR)/, $(testobj))
testobj := $(testobj:.cpp=.o)

#CFLAGS specifies the additional compilation options we're using
CFLAGS := -Wall -Wextra -std=c++17 

#IFLAGS specifies which directory to check for include
IFLAGS := -Isrc

#LFLAGS specifies the libraries we're linking against
LFLAGS  := -lSDL2 -lSDL2_image -lSDL2_mixer bin/libBSDL.a

#WFLAGS specifies that we know what we are doing with ar
WFLAGS := -no_warning_for_no_symbols

#Give us some bold text plz
bold := $(shell tput bold)
sgr0 := $(shell tput sgr0)

#Library Path
ifeq ($(LPATH),)
    LPATH := /usr/lib
endif

#all rule for just compiling everything
.PHONY: all
all: $(bSDLobj) build Tests
	
#Tests for only compiling tests
.PHONY: Tests
Tests: SoundTest TextureTest EventTest WindowTest

.PHONY: build
build: $(bSDLobj)
	@printf "\n$(bold)----------Building bSDL LIB File----------------$(sgr0)\n"
	ar rc bin/libBSDL.a $(bSDLobj)
	ranlib bin/libBSDL.a 

.PHONY: install
install: build
	@printf "\n$(bold)----------INSTALLING LIBRARY TO DIRECTORY-------$(sgr0)\n"
	sudo install -m 644 bin/libBSDL.a $(LPATH)

SoundTest: tests/obj/soundTest.o build
	@printf "\n$(bold)----------COMPILING TEST FILE: $@----------$(sgr0)\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

TextureTest: tests/obj/textureTest.o build
	@printf "\n$(bold)----------COMPILING TEST FILE: $@----------$(sgr0)\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

EventTest: tests/obj/eventTest.o build
	@printf "\n$(bold)----------COMPILING TEST FILE: $@----------$(sgr0)\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

WindowTest: tests/obj/windowTest.o build
	@printf "\n$(bold)----------COMPILING TEST FILE: $@----------$(sgr0)\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

# Rules for bSDL obj files
$(OBJDIR)/%.o: src/*/%.cpp
	@printf "\n$(bold)----------COMPILING BSDL FILE: $(notdir $@)----------$(sgr0)\n"
	$(CC) $^ $(CFLAGS) $(IFLAGS) -c -o $@ 

# Rules for test obj files
$(TESTOBJDIR)/%.o: tests/src/%.cpp
	@printf "\n$(bold)----------COMPILING TEST FILE: $(notdir $@)----------$(sgr0)\n"
	$(CC) $^ $(CFLAGS) $(IFLAGS) -c -o $@ 

.PHONY: clean
clean: 
	@printf "\n$(bold)----------REMOVING PREVIOUS BUILDS----------$(sgr0)\n"
	rm -f $(bSDLobj) 
	rm -f $(testobj)
	rm -f bin/*
	rm -f a.out tests/bin/*
