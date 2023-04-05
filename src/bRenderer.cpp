
#include <iostream>

#include "bRenderer.h"
#include "BML.h"

bRenderer::bRenderer(SDL_Window *window, Uint32 _render_flags) {
	

	// Grabs the SDL_Window()
	_context = window;
    _bkg_color = {255, 255, 255, 255};

	_sdl_renderer = SDL_CreateRenderer(_context, -1, _render_flags);
    SDL_SetRenderDrawBlendMode(_sdl_renderer, SDL_BLENDMODE_BLEND);

    if (_sdl_renderer) {

        SDL_SetRenderDrawColor(_sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a);
        SDL_RenderClear(_sdl_renderer);
        SDL_RenderPresent(_sdl_renderer);
        printf("---  RENDERER SUCCESSFULLY INITIALIZED     ---\n");
    } else {
        printf("---  Renderer Failed to Initialize     ---\n");
        exit(1);
    }


    // Create our managers
    _font_manager = new bFontManager(_sdl_renderer);
    _texture_manager = new bTextureManager(_sdl_renderer);

    // we start with a empty batch
    _batch = nullptr;
}

// Delete our managers
bRenderer::~bRenderer() {

	delete _texture_manager;
	delete _font_manager;
	SDL_DestroyRenderer(_sdl_renderer);
}

// Changes the renderers background color
void bRenderer::background(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    
    _bkg_color = {r, g, b, a};
}

// Clears the current buffer
void bRenderer::clearBuffer() {

    SDL_SetRenderTarget(_sdl_renderer, nullptr);
	SDL_SetRenderDrawColor( _sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a);
    SDL_RenderClear(_sdl_renderer);

    // Start our default batch
    newBatch();
}

// Presents the current buffer
void bRenderer::presentBuffer() {

    // If we have a current batch, push it to the queue
    if (_batch) {
        _atlas_queue.push(_batch);
    }

    SDL_SetRenderTarget(_sdl_renderer, nullptr);

    // While the queue is not empty, render the textures
    while (!_atlas_queue.empty()) {


        // Get the next batch
        SDL_Texture* batch = _atlas_queue.front();
        _atlas_queue.pop();

        // The source rectangle
        SDL_Rect src = {0, 0, 0, 0};

        // Get the size of the batch
        SDL_QueryTexture(batch, nullptr, nullptr, &src.w, &src.h);

        // Destination rectangle
        SDL_Rect dest = {0, 0, src.w, src.h};

        // Render the batch
        SDL_RenderCopy(_sdl_renderer, batch, &src, &dest);

        // Free the batch
        SDL_DestroyTexture(batch);
    }


    // Present the buffer
	SDL_RenderPresent(_sdl_renderer);
    _batch = nullptr;

}

// Presents the current buffer and then clears it for next frame
void bRenderer::drawBuffer() {

	presentBuffer();
	clearBuffer();
}

// Creates a new batch for the texture atlas
void bRenderer::newBatch() {

    // If we have a current batch, push it to the queue
    if (_batch) {
        _atlas_queue.push(_batch);
    }

    int width, height;
    SDL_GetRendererOutputSize(_sdl_renderer, &width, &height);
    _batch = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

    // Set the render target to the current atlas
    SDL_SetRenderTarget(_sdl_renderer, _batch);

    SDL_SetRenderDrawColor(_sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a); // Set the draw color to transparent black
    SDL_RenderClear(_sdl_renderer); // Clear the render target

}

// Initalizes a texutre from the texture manager and returns it 
bTexture bRenderer::initTexture(const char* source, bRect src) {

    return _texture_manager -> loadTexture(source, src);
}

// Initializes a spritesheet using our texture manager
void bRenderer::initSpriteSheet(bSheet &sheet) {
   
    bTexture newTexture;

    newTexture = _texture_manager -> loadTexture(sheet.imagePath.c_str(), {0, 0, sheet.totalWidth, sheet.totalHeight});
    sheet.sourceTexture = newTexture;
}


// Draws a texture to the screen
void bRenderer::drawTexture(bTexture texture, bRect dest) {

    _texture_manager -> renderTexture(texture, dest);
}

void bRenderer::drawTexture(bTexture texture, bPoint dest) {

    _texture_manager -> renderTexture(texture, dest);
}

// Initalizes and adds a texture to render scene then frees texture
// Awful don't use :3
void bRenderer::drawTexture(const char* source, bRect src, bRect dest) {

    bTexture newTexture = _texture_manager -> loadTexture(source, src);
    _texture_manager -> renderTexture(newTexture, dest);
    _texture_manager -> unloadTexture(newTexture);
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

// Simply drawing a rectangle
void bRenderer::drawRect(bRect location, SDL_Color color) {


    SDL_Rect SDL_location = {(int)location.x, (int)location.y, (int)location.width, (int)location.height};
    SDL_SetRenderDrawColor( _sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_sdl_renderer, &SDL_location);
    SDL_SetRenderDrawColor( _sdl_renderer, 0, 0, 0, 255 );
}

// Unloads a texture from memory
void bRenderer::unloadTexture(bTexture &texture) {

    _texture_manager -> unloadTexture(texture);
}

// Just calls unloadTexture() on the sheet's source texture
void bRenderer::unloadSpriteSheet(bSheet &sheet) {

    this->unloadTexture(sheet.sourceTexture);
}

void bRenderer::setFont(std::string filePath, Uint8 font_size, SDL_Color color) {

    _font_manager -> setFont(filePath, font_size, color);
}
void bRenderer::drawText(std::string text, bPoint position) {

    _font_manager -> render(text, position);
}
