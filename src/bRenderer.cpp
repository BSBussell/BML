
#include <iostream>

#include "bRenderer.h"
#include "BML.h"

bRenderer::bRenderer(SDL_Window *window, Uint32 _render_flags) {
	

	// Grabs the SDL_Window()
	_context = window;
    _bkg_color = {255, 255, 255, 255};

    // Check if high DPI is enabled
    _hi_dpi = (SDL_GetWindowFlags(_context) & SDL_WINDOW_ALLOW_HIGHDPI);


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

    int width, height;
    SDL_GetRendererOutputSize(_sdl_renderer, &width, &height);
    _dimensions = {width, height};


    // Testing Creation of a bigger buffer than the rendering space
    width *= (1.0f / _min_zoom.x);
    height *= (1.0f / _min_zoom.y);
    _buffer = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
}

// Delete our managers
bRenderer::~bRenderer() {

    // Delete our managers
	delete _texture_manager;
	delete _font_manager;

    // We are mixing C and C++ memory allocations
    SDL_DestroyTexture(_buffer);
    SDL_DestroyRenderer(_sdl_renderer);

}

// Changes the renderers background color
void bRenderer::background(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    
    _bkg_color = {r, g, b, a};
}

// Clears the current buffer, it is essential to call this before drawing
void bRenderer::clearBuffer() {

    // Set the void color
    SDL_SetRenderDrawColor( _sdl_renderer, 0, 0, 0, 0);


    // Clear the screen
    SDL_SetRenderTarget(_sdl_renderer, nullptr);
    SDL_RenderClear(_sdl_renderer);

    // Clear the buffer
    SDL_SetRenderTarget(_sdl_renderer, _buffer);
    SDL_SetRenderDrawColor( _sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a);
    SDL_RenderClear(_sdl_renderer);
}

// Presents the current buffer
void bRenderer::presentBuffer() {

    // Present the framebuffer
    SDL_SetRenderTarget(_sdl_renderer, NULL);


    // Set up the camera transformation
    SDL_Rect transformed;
    transformed.x = 0;
    transformed.y = 0;

    // Here we are sizing the Source rect to the size of the zoom
    transformed.w = _dimensions.x * ( 1.0 / _camera_scale.x );
    transformed.h = _dimensions.y * ( 1.0 / _camera_scale.y );

    SDL_Rect src;

    // Here we are sizing the source rect to the size of the zoom
    src.x = 0;
    src.y = 0;

    // Here we are sizing the destination rect to the size of the zoom
    src.w = _dimensions.x * ( 1.0 / _camera_scale.x );
    src.h = _dimensions.y * ( 1.0 / _camera_scale.y );


    printf("Camera Scale (%f, %f)\n", _camera_scale.x, _camera_scale.y);


    // Set the scale
    SDL_RenderSetScale(_sdl_renderer, _camera_scale.x, _camera_scale.y);

    // Render the buffer
    SDL_RenderCopyEx(_sdl_renderer, _buffer, &src, &transformed, _camera_angle, NULL, SDL_FLIP_NONE);

    // Reset the scale
    SDL_RenderSetScale(_sdl_renderer, 1, 1);

    // Present the buffer
	SDL_RenderPresent(_sdl_renderer);

}

// Presents the current buffer and then clears it for next frame
void bRenderer::drawBuffer() {

	presentBuffer();
	clearBuffer();
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

    // Apply the camera transformation
    dest.x -= _camera_position.x;
    dest.y -= _camera_position.y;



    _texture_manager -> renderTexture(texture, dest);
}

// Draws a texture to the screen at a given point
void bRenderer::drawTexture(bTexture texture, bPoint dest) {

    bRect destRect;
    destRect.x = dest.x;
    destRect.y = dest.y;
    destRect.width = static_cast<Uint32>(texture.src.w);
    destRect.height = static_cast<Uint32>(texture.src.h);

    drawTexture(texture, destRect);
}


// Draws a sprite by grabbing from the texture and then drawing that specific region
void bRenderer::drawSprite(bSheet &sheet, bRect dest) {

    // If the sheet is animated, update the animation
    if (sheet.animated)
        sheet.updateAnimation();
    
    // Converting the rects we're given into the appropriate rects
    SDL_Rect SDL_src = SDL_Rect(sheet.sprites[sheet.currentSprite]);

    // Set the source texture to the given sprite
    sheet.sourceTexture.src = SDL_src;

    // Draw the bTexture at the destination
    drawTexture(sheet.sourceTexture, dest);

    // Reset the source texture to the entire spritesheet
    sheet.sourceTexture.src = {0, 0, sheet.sourceTexture.src.w, sheet.sourceTexture.src.h};

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

    unloadTexture(sheet.sourceTexture);
}

void bRenderer::setFont(std::string filePath, Uint8 font_size, SDL_Color color) {

    _font_manager -> setFont(filePath, font_size, color);
}
void bRenderer::drawText(std::string text, bPoint position) {

    // Adjust position to camera's position
    position.x -= _camera_position.x;
    position.y -= _camera_position.y;

    _font_manager -> render(text, position);
}

// Sets the camera's transformations
void bRenderer::setCameraTransformations(bPoint position, bPointF scale, double angle) {

//    // If the scale has changed, we need to resize the buffer
//    if (_camera_scale.x != scale.x || _camera_scale.y != scale.y) {
//
//        _camera_scale = scale;
//
//        // Calculate the new dimensions
//        SDL_Point resize;
//        resize.x = _dimensions.x / scale.x;
//        resize.y = _dimensions.y / scale.y;
//
//        printf("Resized Buffer Dimensions: %d, %d\n", resize.x, resize.y);
//
//
//        // Create the new buffer
//        SDL_Texture *_new_buffer = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,resize.x, resize.y);
//
//        // Setup the new buffer to be drawn to
//        SDL_SetRenderTarget(_sdl_renderer, _new_buffer);
//        SDL_SetRenderDrawColor(_sdl_renderer, _bkg_color.r, _bkg_color.g, _bkg_color.b, _bkg_color.a);
//        SDL_RenderClear(_sdl_renderer);
//
//        SDL_Rect new_dimensions;
//        new_dimensions.x = 0;
//        new_dimensions.y = 0;
//        new_dimensions.w = _dimensions.x;
//        new_dimensions.h = _dimensions.y;
//
//        // Copy the old buffer to the new buffer
//        SDL_RenderCopy(_sdl_renderer, _buffer, NULL, &new_dimensions);
//
//        // Delete the old buffer
//        SDL_DestroyTexture(_buffer);
//
//        // Set the new buffer to be the current buffer
//        _buffer = _new_buffer;
//
//        // Set the updated Scaling
//        _camera_scale = scale;
//
//        _dimensions = resize;
//    }


    _camera_scale = scale;
    _camera_position = position;
    _camera_angle = angle;

    // Floor the camera zoom
    if (_camera_scale.x < _min_zoom.x)
        _camera_scale.x = _min_zoom.x;
    if (_camera_scale.y < _min_zoom.y)
        _camera_scale.y = _min_zoom.y;
}

void bRenderer::setMinZoom(bPointF min_zoom) {

    // Resize the framebuffer if changing the min zoom
    if (_min_zoom.x != min_zoom.x || _min_zoom.y != min_zoom.y) {

        // Calculate the new buffer size
        SDL_Point resize;
        resize.x = _dimensions.x * (1.0f / min_zoom.x);
        resize.y = _dimensions.y * (1.0f / min_zoom.y);

        // Delete the old buffer
        SDL_DestroyTexture(_buffer);

        // Create the new buffer
        _buffer = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,resize.x, resize.y);

        // Clear the new buffer
        clearBuffer();
    }

    _min_zoom = min_zoom;
}

void bRenderer::resizeToWindow() {

    // Get the Window from a secret function :3
    SDL_Window *_window =  SDL_RenderGetWindow(_sdl_renderer);

    // Get the window's dimensions
    SDL_GetWindowSize(_window, &_dimensions.x, &_dimensions.y);

    if (_hi_dpi)
        

    // Delete the old buffer
    SDL_DestroyTexture(_buffer);

    // Create the new buffer
    _buffer = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,_dimensions.x, _dimensions.y);

    // Clear the new buffer
    clearBuffer();
}