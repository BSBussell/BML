// Bee Bussell
// Sep 8, 2021
// Initalization Functions

#include "BML.h"

void BML_Init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("---   SDL %d.%d.%d SUCCESSFULLY INITIALIZED  ---\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
	} else {
		printf("---       SDL FAILED TO INITIALIZE          ---\n");
		printf("Unable to initialize SDL: %s", SDL_GetError());
	}
}

void BML_Close() {

	SDL_Quit();
}

std::string BML_GetPath(const char* path) {

	// Get SDL_BasePath

	char *base_path = SDL_GetBasePath();
	std::string base_path_string = std::string(base_path);
	std::string full_path = base_path_string + std::string(path);

	// Making me nostalgic for CS360
	SDL_free(base_path);

    return full_path;

}

std::string BML_GetPath(std::string path) {

	char *base_path = SDL_GetBasePath();
	std::string base_path_string = std::string(base_path);
	std::string full_path = base_path_string + path;

	// Lol C
	SDL_free(base_path);

    return full_path;
}


//Uint64 BML_GetTicks() {
//    #if SDL_VERSION_ATLEAST(2, 0, 18)  // Zorin is behind on their SDL versions
//        return SDL_GetTicks64();
//    #else
//        return static_cast<Uint64>(SDL_GetTicks());
//    #endif
//}
