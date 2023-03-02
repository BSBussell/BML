
// Bee Bussell
// Sept 6, 2021
// Header

#ifndef BTEXTURE_H
#define BTEXTURE_H

#include <SDL2/SDL.h>

// Just a header file for now

// TODO: Implement texture freeing and destructer for that

struct bTexture {

	SDL_Texture* texture;
	SDL_Rect src;
};


#endif
