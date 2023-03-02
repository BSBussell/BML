
// Bee Bussell
// Sept 6, 2021
// Creating Rectangless

#ifndef BRECT_H
#define BRECT_H

#include <SDL2/SDL.h>
#include <cstdint>
 
struct bRect {

	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;

    operator SDL_Rect() const;

};

#endif
