
// Bee Bussell
// Sept 6, 2021
// Header

#ifndef bTexture_h
#define bTexture_h

#include <SDL2/SDL.h>
#include <stdint.h>

class bTexture {

public:

	bTexture();
	~bTexture();

private:

	bRect src;
    bRect dest;

};






#endif
