
// Bee Bussell
// Sept 6, 2021
// Creating Rectangless

#ifndef bRect_h
#define bRect_h

#include <SDL2/SDL.h>
#include <cstdint>

struct bRect {

	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;

    SDL_Rect sdl_Rect();

};

#endif
