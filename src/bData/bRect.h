
// Bee Bussell
// Sept 6, 2021
// Creating Rectangless

#ifndef bRect_h
#define bRect_h

#include <SDL2/SDL.h>

struct bRect {

	double x;
	double y;
	double width;
	double height;

    SDL_Rect sdl_rect() {

        SDL_Rect translation = {(int)x, (int)y, (int)width, (int)height};
        return translation;
    };

};

#endif
