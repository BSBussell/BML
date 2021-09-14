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

	std::string relativePath = std::string(SDL_GetBasePath());
    relativePath += std::string(path);

    return relativePath;

}
