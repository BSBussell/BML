// Bee Bussell
// Sep 8, 2021
// Initalization Functions

#include "BML.h"


void BML_Init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("---       SDL SUCCESSFULLY INITALIZED      ---\n");
	} else {
		printf("---       SDL FAILED TO INITALIZE          ---\n");
		printf("Unable to initialize SDL: %s", SDL_GetError());
	}
}

void BML_Close() {

	SDL_Quit();
}