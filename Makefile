#OBJS specifies which files to compile as part of the project
#Initalize when doing more stuff



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
LFLAGS  := -lSDL2 -lSDL2_image -lSDL2_mixer bin/bSDL.a

#WFLAGS specifies that we know what we are doing with ar
WFLAGS := -no_warning_for_no_symbols

#all rule for just compiling everything
.PHONY: all
all: $(bSDLobj) build Tests
	
#Tests for only compiling tests
.PHONY: Tests
Tests: SoundTest TextureTest EventTest WindowTest

.PHONY: build
build: $(bSDLobj)
	@echo "\n----------------Building bSDL LIB File----------------\n"
	ar rc bin/bSDL.a $(bSDLobj)
	ranlib bin/bSDL.a $(WFLAGS)

SoundTest: tests/obj/soundTest.o build
	@echo "\n----------COMPILING TEST FILE: " $@ "----------\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

TextureTest: tests/obj/textureTest.o build
	@echo "\n----------COMPILING TEST FILE: " $@ "----------\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

EventTest: tests/obj/eventTest.o build
	@echo "\n----------COMPILING TEST FILE: " $@ "----------\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

WindowTest: tests/obj/windowTest.o build
	@echo "\n----------COMPILING TEST FILE: " $@ "----------\n"
	$(CC) $< $(CFLAGS) $(LFLAGS) -o tests/bin/$@

# Rules for bSDL obj files
$(OBJDIR)/%.o: src/*/%.cpp
	@echo "\n----------COMPILING BSDL FILE:  " $(notdir $@) "----------\n"
	$(CC) $^ $(CFLAGS) $(IFLAGS) -c -o $@ 

# Rules for test obj files
$(TESTOBJDIR)/%.o: tests/src/%.cpp
	@echo "\n----------COMPILING TEST FILE: " $(notdir $@) "----------\n"
	$(CC) $^ $(CFLAGS) $(IFLAGS) -c -o $@ 

.PHONY: clean
clean: 
	@echo "\n----------REMOVING PREVIOUS BUILDS----------\n"
	rm -f $(bSDLobj) 
	rm -f $(testobj)
	rm -f bin/*
	rm -f a.out tests/bin/*
