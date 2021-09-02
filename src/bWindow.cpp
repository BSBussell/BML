
// Bee Bussell
// Sept 1, 2021
// Wraps the SDL window and renderer class together

#include <iostream>

#include "bWindow.h"

bWindow::~bWindow() {

}

void bWindow::createWindow() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        printf("...     SDL Successfully Initialized     ...\n");
        
        sdlWindow = SDL_CreateWindow(windowTitle, xPos, yPos, width, height, flags);
        
        if (sdlWindow) {
            SDL_UpdateWindowSurface(sdlWindow);
            printf("...  Window Successfully Initialized     ...\n");
        } else
            printf("...Window Failed to Initialize...\n");

        sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
        
        if (sdlRenderer) {
            
            SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
            SDL_RenderClear(sdlRenderer);
            SDL_RenderPresent(sdlRenderer);
            printf("...Renderer Successfully Initialized     ...\n");
        } else 
            printf("...Renderer Failed to Initialize...\n");

    } else
        printf("...SDL Failed to Initialize...\n");

}
