
// Bee Bussell
// Sept 1, 2021
// Wraps the SDL window and renderer class together

#include <iostream>

#include "bWindow.h"
#include "BML.h"

bWindow::~bWindow() {

    closeWindow();
}

// Creates the window
// Creates the renderer
bRenderer *bWindow::createWindow() {


    sdlWindow = SDL_CreateWindow(windowTitle, xPos, yPos, width, height, windowFlags);

    if (sdlWindow) {
        SDL_UpdateWindowSurface(sdlWindow);
        printf("---    WINDOW SUCCESSFULLY INITIALIZED     ---\n");
    } else {
        printf("---  Window Failed to Initialize     ---\n");
        exit(1);
    }

    _renderer = new bRenderer(sdlWindow, _render_flags);
    
    return _renderer;
}



// Deletes the renderer
// Deletes the window
void bWindow::closeWindow() {

    // See bRenderer destructor :3
    delete _renderer;
    SDL_DestroyWindow(sdlWindow);
}
