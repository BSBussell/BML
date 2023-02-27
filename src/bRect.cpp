// Bee Bussell
// Sept 7, 2021
// For Compilation


#include "bRect.h"

bRect::operator SDL_Rect() const {

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	return rect;

}

