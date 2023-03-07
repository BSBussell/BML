
// Bee Bussell
// March 7, 2023
// bRenderer

#ifndef BML_RENDERER_H
#define BML_RENDERER_H

#include "BML.h"

class bRenderer {
	
public:

	bRenderer();
	~bRenderer();

	// Renderer Flag Toggles
    void toggleSoftwareRender() { renderFlags ^= SDL_RENDERER_SOFTWARE; }
    void toggleHardwareRender() { renderFlags ^= SDL_RENDERER_ACCELERATED; }
    void toggleVSync() { renderFlags ^= SDL_RENDERER_PRESENTVSYNC; } 
    void toggleToTexture() { renderFlags ^= SDL_RENDERER_TARGETTEXTURE; }

    // Buffer Presentation
    void clearBuffer();
    void updateBuffer();
    void drawBuffer();

    // Change the background color
    void background(uint8_t r, uint8_t g, uint8_t b, uint8_t a);


    // Initalize Textures
    bTexture initTexture(const char* source, bRect src);
    void initSpriteSheet(bSheet &sheet);

    // Drawing Textures and Rectangles
    void drawTexture(bTexture texture, bRect dest);
    void drawTexture(const char* source, bRect src, bRect dest);
    void drawSprite(bSheet &sheet, bRect dest);
    void drawRect(bRect location, uint8_t r, uint8_t g, uint8_t b);

    // Freeing Textures
    void freeTexture(bTexture &texture);
    void freeSpriteSheet(bSheet &sheet);

    // Fonts
    void setFont(std::string filePath, Uint8 font_size, SDL_Color color);
    void drawText(std::string text, bPoint position);

private:

	bFontManager *font_manager;

	SDL_Color _bkg_color;

	SDL_Window *context;
	SDL_Renderer *_sdl_renderer;

	uint32_t renderFlags = 0;
}


#endif