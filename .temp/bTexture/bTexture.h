
// Bee Bussell
// Sept 6, 2021
// Header

#ifndef bTexture_h
#define bTexture_h

#include <SDL2/SDL.h>

// Just a header file for now

// TODO: Implement texture freeing and destructer for that

struct bTexture {

	SDL_Texture* texture;
	SDL_Rect src;
};


#endif
