
// Bee Bussell
// Sept 1, 2021
// Wraps the SDL window and renderer class together

#include <iostream>

#include "bWindow.h"

bWindow::~bWindow() {

    closeWindow();
}

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

void bWindow::closeWindow() {

    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyRenderer(sdlRenderer);
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

bTexture bWindow::initSpriteSheet(bSheet &sheet) {
    
    bTexture newTexture;
    SDL_Surface* surface = IMG_Load(BML_GetPath(sheet.imagePath).c_str());
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);

    newTexture.texture = sdlTexture;
    newTexture.src = {0, 0, (int)sheet.totalWidth, (int)sheet.totalHeight};

    sheet.sourceTexture = newTexture;

    return newTexture;
}

void bWindow::drawTexture(bTexture texture, bRect dest) {

    SDL_Rect SDL_dest = SDL_Rect(dest); 

    SDL_RenderCopy(sdlRenderer, texture.texture, &texture.src, &SDL_dest);
}

// Initalizes and adds a texture to render scene
void bWindow::drawTexture(const char* source, bRect src, bRect dest) {

    SDL_Surface* surface = IMG_Load(source);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect SDL_src = SDL_Rect(src); 
    SDL_Rect SDL_dest = SDL_Rect(dest); 

    SDL_RenderCopy(sdlRenderer, texture, &SDL_src, &SDL_dest);

}

void bWindow::drawSprite(bSheet sheet, bRect dest) {

    SDL_Rect SDL_dest = SDL_Rect(dest);
    SDL_Rect SDL_src = SDL_Rect(sheet.sprites[sheet.currentSprite]);

    SDL_RenderCopy(sdlRenderer, sheet.sourceTexture.texture, &SDL_src, &SDL_dest);

}

void bWindow::drawRect(bRect location, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) {


    SDL_Rect SDL_location = {(int)location.x, (int)location.y, (int)location.width, (int)location.height};
    SDL_SetRenderDrawColor( sdlRenderer, r, g, b, 255);
    SDL_RenderDrawRect(sdlRenderer, &SDL_location);
    SDL_SetRenderDrawColor( sdlRenderer, 0, 0, 0, 255 );
}

