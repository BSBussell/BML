
// Bee Bussell
// March 7, 2023
// bRenderer

#ifndef BML_RENDERER_H
#define BML_RENDERER_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "bFontManager.h"
#include "bTexture.h"
#include "bSheet.h"


class bRenderer {
	
public:

	bRenderer(SDL_Window *window, Uint32 _render_flags);
	~bRenderer();

    // Change the background color
    void background(uint8_t r, uint8_t g, uint8_t b, uint8_t a);


    // Buffer Presentation
    void clearBuffer();
    void presentBuffer();
    void drawBuffer();

    // Initalize Textures
    bTexture initTexture(const char* source, bRect src);
    void initSpriteSheet(bSheet &sheet);

    // Drawing Textures and Rectangles
    void drawTexture(bTexture texture, bRect dest);
    void drawTexture(const char* source, bRect src, bRect dest);
    void drawSprite(bSheet &sheet, bRect dest);
    void drawRect(bRect location, uint8_t r, uint8_t g, uint8_t b);

    // Freeing Textures
    void unloadTexture(bTexture &texture);
    void unloadSpriteSheet(bSheet &sheet);

    // Fonts
    void setFont(std::string filePath, Uint8 font_size, SDL_Color color);
    void drawText(std::string text, bPoint position);

private:

	bFontManager *_font_manager;

	SDL_Color _bkg_color;

	SDL_Window *_context;
	SDL_Renderer *_sdl_renderer;

};


#endif