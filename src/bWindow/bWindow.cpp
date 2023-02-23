
// Bee Bussell
// Sept 1, 2021
// Wraps the SDL window and renderer class together

#include <iostream>

#include "bWindow.h"

bWindow::~bWindow() {

    closeWindow();
}

// Creates the window
// Creates the renderer
bool bWindow::createWindow() {


    sdlWindow = SDL_CreateWindow(windowTitle, xPos, yPos, width, height, windowFlags);

    if (sdlWindow) {
        SDL_UpdateWindowSurface(sdlWindow);
        printf("---    Window Successfully Initialized     ---\n");
    } else {
        printf("---  Window Failed to Initialize     ---\n");
        return false;
    }

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, renderFlags);

    if (sdlRenderer) {

        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderPresent(sdlRenderer);
        printf("---  Renderer Successfully Initialized     ---\n");
    } else {
        printf("---  Renderer Failed to Initialize     ---\n");
        return false;
    }

    return true;
}

void bWindow::clearBuffer() {

    SDL_RenderClear(sdlRenderer);
}

void bWindow::updateBuffer() {

    SDL_RenderPresent(sdlRenderer);

}

void bWindow::drawBuffer() {

    updateBuffer();
    clearBuffer();
}

// Deletes the renderer
// Deletes the window
void bWindow::closeWindow() {


    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

bTexture bWindow::initTexture(const char* source, bRect src) {

    bTexture newTexture;
    SDL_Surface* surface = IMG_Load(BML_GetPath(source).c_str());
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);

    newTexture.texture = sdlTexture;
    newTexture.src = {(int)src.x, (int)src.y, (int)src.width, (int)src.height};

    return newTexture;
}

void bWindow::initSpriteSheet(bSheet &sheet) {

    // Making a new texture ok    
    bTexture newTexture;

    // Grabbing the surface
    SDL_Surface* surface = IMG_Load(BML_GetPath(sheet.imagePath).c_str());
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    
    // Used the surface to make a texture now free it... Seems to cause no problems
    SDL_FreeSurface(surface);

    newTexture.texture = sdlTexture;
    newTexture.src = {0, 0, (int)sheet.totalWidth, (int)sheet.totalHeight};

    sheet.sourceTexture = newTexture;
}

void bWindow::freeTexture(bTexture &texture) {

    SDL_DestroyTexture(texture.texture);
}

void bWindow::freeSpriteSheet(bSheet &sheet) {

    this->freeTexture(sheet.sourceTexture);
}

void bWindow::drawTexture(bTexture texture, bRect dest) {

    SDL_Rect SDL_dest = SDL_Rect(dest); 

    SDL_RenderCopy(sdlRenderer, texture.texture, &texture.src, &SDL_dest);
}

// Initalizes and adds a texture to render scene
// Awful don't use :3
void bWindow::drawTexture(const char* source, bRect src, bRect dest) {

    SDL_Surface* surface = IMG_Load(source);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect SDL_src = SDL_Rect(src); 
    SDL_Rect SDL_dest = SDL_Rect(dest); 

    SDL_RenderCopy(sdlRenderer, texture, &SDL_src, &SDL_dest);

}

// Draws a sprite by grabbing from the texture and then drawing that specific region
void bWindow::drawSprite(bSheet &sheet, bRect dest) {

    if (sheet.animated)
        sheet.updateAnimation();
    
    // Converting the rects we're given into the appropriate rects
    SDL_Rect SDL_dest = SDL_Rect(dest);
    SDL_Rect SDL_src = SDL_Rect(sheet.sprites[sheet.currentSprite]);

    // print to the renderer the texture at the coordinates
    SDL_RenderCopy(sdlRenderer, sheet.sourceTexture.texture, &SDL_src, &SDL_dest);
}

void bWindow::drawRect(bRect location, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) {


    SDL_Rect SDL_location = {(int)location.x, (int)location.y, (int)location.width, (int)location.height};
    SDL_SetRenderDrawColor( sdlRenderer, r, g, b, 255);
    SDL_RenderFillRect(sdlRenderer, &SDL_location);
    SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 255 );
    //free(SDL_location);
}

