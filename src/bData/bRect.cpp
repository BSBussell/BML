// Bee Bussell
// Sept 7, 2021
// For Compilation


#include "bRect.h"

SDL_Rect bRect::sdl_Rect() {

	SDL_Rect rect;
	rect.x = (int)x;
	rect.y = (int)y;
	rect.w = (int)width;
	rect.h = (int)height;

	return rect;

}