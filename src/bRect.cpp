// Bee Bussell
// Sept 7, 2021
// Conversion functions


#include "bRect.h"

bRect::operator SDL_Rect() const {

	SDL_Rect rect;
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);
    return rect;

}

bPoint::operator SDL_Point() const {

	SDL_Point point;
	point.x = static_cast<int>(x);
    point.y = static_cast<int>(y);
	return point;
}

