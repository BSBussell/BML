// Bee Bussell
// Sep 8, 2021
// Initalization Functions

#include "BML.h"


void BML_Init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("---       SDL SUCCESSFULLY INITIALIZED      ---\n");
	} else {
		printf("---       SDL FAILED TO INITIALIZE          ---\n");
		printf("Unable to initialize SDL: %s", SDL_GetError());
	}
}

void BML_Close() {

	SDL_Quit();
}

std::string BML_GetPath(const char* path) {

	char * base_path = SDL_GetBasePath();

	std::string relativePath = std::string(base_path);
    relativePath += std::string(path);
	
	// SDL being a C library always causes some funnies
	// Maybe I should be rewriting this in C lmao
	free(base_path);

    return relativePath;

}

std::string BML_GetPath(std::string path) {

	char * base_path = SDL_GetBasePath();

	std::string relativePath = std::string(base_path);
    relativePath += path;

	// holy hell :3
	free(base_path);

    return relativePath;

}
