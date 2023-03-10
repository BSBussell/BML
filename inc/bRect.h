
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
 
 /**
  * @brief A struct for holding a 2D point
  * 
  */
struct bPoint {

	Uint32 x, y;

	/**
	 * @brief Converts to SDL_Point
	 * 
	 * @return SDL_Point 
	 */
	operator SDL_Point() const;
};

/**
 * @brief A struct for holding a 2D rectangle
 * 
 */
struct bRect {

	Uint32 x;
	Uint32 y;
	Uint32 width;
	Uint32 height;

	/**
	 * @brief Converts to SDL_Rect
	 * 
	 * @return SDL_Rect 
	 */
    operator SDL_Rect() const;

};

#endif
