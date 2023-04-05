
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

    // Create the renderer using the given flags
	bRenderer(SDL_Window *window, Uint32 _render_flags);
    // Delete our managers
	~bRenderer();

    // Change the background color
    void background(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    // Buffer Presentation
    void clearBuffer();
    void presentBuffer();
    void drawBuffer();

    // Batch Rendering
    void newBatch();

    // Initalize Textures
    bTexture initTexture(const char* source, bRect src);
    void initSpriteSheet(bSheet &sheet);

    // Drawing Textures and Rectangles
    void drawTexture(bTexture texture, bRect dest);
    void drawTexture(bTexture texture, bPoint dest);
    void drawTexture(const char* source, bRect src, bRect dest);
    void drawSprite(bSheet &sheet, bRect dest);
    void drawRect(bRect location, SDL_Color color);

    // Freeing Textures
    void unloadTexture(bTexture &texture);
    void unloadSpriteSheet(bSheet &sheet);

    // Fonts
    void setFont(std::string filePath, Uint8 font_size, SDL_Color color);
    void drawText(std::string text, bPoint position);

private:

    /*
        We want our managers to be stored in the heap because
        they will have a long life time, and we don't want to 
        overfill the stack with things
    */
    bTextureManager *_texture_manager;
	bFontManager *_font_manager;

	SDL_Window *_context;
	SDL_Renderer *_sdl_renderer;

    // The background color
    SDL_Color _bkg_color;

    // The Texture Atlas
    SDL_Texture *_batch;


    // @brief A Queue of texture atlases
    std::queue<SDL_Texture*> _atlas_queue;

};


#endif