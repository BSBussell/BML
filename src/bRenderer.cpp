
#include <iostream>

#include "bRenderer.h"
#include "BML.h"

bRenderer::bRenderer(SDL_Window *window, Uint32 _render_flags) {
	

	// Grabs the SDL_Window()
	_context = window;

	_sdl_renderer = SDL_CreateRenderer(_context, -1, _render_flags);

    if (_sdl_renderer) {

        SDL_SetRenderDrawColor(_sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a);
        SDL_RenderClear(_sdl_renderer);
        SDL_RenderPresent(_sdl_renderer);
        printf("---  RENDERER SUCCESSFULLY INITIALIZED     ---\n");
    } else {
        printf("---  Renderer Failed to Initialize     ---\n");
        exit(1);
    }

    _font_manager = new bFontManager(_sdl_renderer);    

}

bRenderer::~bRenderer() {
	
	delete _font_manager;
	SDL_DestroyRenderer(_sdl_renderer);
}

void bRenderer::background(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    
    _bkg_color = {r, g, b, a};
}

void bRenderer::clearBuffer() {
	
	SDL_SetRenderDrawColor( _sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a);
    SDL_RenderClear(_sdl_renderer);
    //SDL_SetRenderDrawColor( _sdl_renderer, 0, 0, 0, 0);
}

void bRenderer::presentBuffer() {

	SDL_RenderPresent(_sdl_renderer);
}

void bRenderer::drawBuffer() {

	presentBuffer();
	clearBuffer();
}

bTexture bRenderer::initTexture(const char* source, bRect src) {

    bTexture newTexture;

    // Despite SDL_LoadTexture's existence I would like to keep the
    // SDL_Surface in case :3
    SDL_Surface* surface = IMG_Load(BML_GetPath(source).c_str());
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);
    SDL_FreeSurface(surface);

    newTexture.texture = sdlTexture;
    newTexture.src = {(int)src.x, (int)src.y, (int)src.width, (int)src.height};

    return newTexture;
}

void bRenderer::initSpriteSheet(bSheet &sheet) {

    // Making a new texture ok    
    bTexture newTexture;

    // Grabbing the surface
    SDL_Surface* surface = IMG_Load(BML_GetPath(sheet.imagePath).c_str());
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);
    
    // Used the surface to make a texture now free it... Seems to cause no problems
    SDL_FreeSurface(surface);

    newTexture.texture = sdlTexture;
    newTexture.src = {0, 0, (int)sheet.totalWidth, (int)sheet.totalHeight};

    sheet.sourceTexture = newTexture;
}


void bRenderer::drawTexture(bTexture texture, bRect dest) {

    SDL_Rect SDL_dest = SDL_Rect(dest); 

    SDL_RenderCopy(_sdl_renderer, texture.texture, &texture.src, &SDL_dest);
}

// Initalizes and adds a texture to render scene
// Awful don't use :3
void bRenderer::drawTexture(const char* source, bRect src, bRect dest) {

    SDL_Surface* surface = IMG_Load(source);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect SDL_src = SDL_Rect(src); 
    SDL_Rect SDL_dest = SDL_Rect(dest); 

    SDL_RenderCopy(_sdl_renderer, texture, &SDL_src, &SDL_dest);

}

// Draws a sprite by grabbing from the texture and then drawing that specific region
void bRenderer::drawSprite(bSheet &sheet, bRect dest) {

    if (sheet.animated)
        sheet.updateAnimation();
    
    // Converting the rects we're given into the appropriate rects
    SDL_Rect SDL_dest = SDL_Rect(dest);
    SDL_Rect SDL_src = SDL_Rect(sheet.sprites[sheet.currentSprite]);

    // print to the renderer the texture at the coordinates
    SDL_RenderCopy(_sdl_renderer, sheet.sourceTexture.texture, &SDL_src, &SDL_dest);
}

void bRenderer::drawRect(bRect location, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) {


    SDL_Rect SDL_location = {(int)location.x, (int)location.y, (int)location.width, (int)location.height};
    SDL_SetRenderDrawColor( _sdl_renderer, r, g, b, 255);
    SDL_RenderFillRect(_sdl_renderer, &SDL_location);
    SDL_SetRenderDrawColor( _sdl_renderer, 0, 0, 0, 255 );
    //free(SDL_location);
}

void bRenderer::unloadTexture(bTexture &texture) {

    SDL_DestroyTexture(texture.texture);
}

void bRenderer::unloadSpriteSheet(bSheet &sheet) {

    this->unloadTexture(sheet.sourceTexture);
}

void bRenderer::setFont(std::string filePath, Uint8 font_size, SDL_Color color) {

    _font_manager -> setFont(filePath, font_size, color);
}
void bRenderer::drawText(std::string text, bPoint position) {

    _font_manager -> render(text, position);
}
