
// Bee Bussell
// Sept 1, 2021
// Wraps the SDL window and renderer class together

#include <iostream>

#include "bWindow.h"

bWindow::~bWindow() {

}

void bWindow::createWindow() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        printf("...SDL Successfully Initialized...");
        
        sdlWindow = SDL_CreateWindow(windowTitle, xPos, yPos, width, height, flags);
        
        if (sdlWindow)
            printf("...Window Successfully Initialized...");
        else
            printf("...Window Failed to Initialize...");

        sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
        
        if (sdlRenderer) {
            SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
            printf("...Renderer Successfully Initialized...");
        } else 
            printf("...Renderer Failed to Initialize...");

    } else
        printf("...SDL Failed to Initialize...");

}
