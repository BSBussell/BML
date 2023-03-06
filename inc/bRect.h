
// Bee Bussell
// Sept 6, 2021
// Creating Rectangles and more

/*
	Might seem pointless but eventually I plan on baking methods into these
*/

#ifndef BML_RECT_H
#define BML_RECT_H

#include <SDL2/SDL.h>
#include <cstdint>
 
struct bPoint {

	uint32_t x, y;

	// Easy conversion to SDL_Point
	operator SDL_Point() const;
};

struct bRect {

	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;

	// Easy conversion to SDL_Rect
    operator SDL_Rect() const;

};

#endif
