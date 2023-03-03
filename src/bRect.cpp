// Bee Bussell
// Sept 7, 2021
// Conversion functions


#include "bRect.h"

bRect::operator SDL_Rect() const {

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	return rect;

}

bPoint::operator SDL_Point() const {

	SDL_Point point;
	point.x = x;
	point.y = y;

	return point;
}

