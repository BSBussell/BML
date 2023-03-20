
// Bee Bussell
// Sept 1, 2021
// Header

#ifndef BML_WINDOW_H
#define BML_WINDOW_H


#include "bRenderer.h"

class bWindow {

public:

    // Constructors and Destroyer
    bWindow(const char *windowTitle, Uint16 xPos, Uint16 yPos, Uint16 width, Uint16 height)
        : windowTitle(windowTitle)
        , xPos(xPos)
        , yPos(yPos)
        , width(width)
        , height(height)
    { }
    ~bWindow();

    // Window Dimensions and Position Setters
    void move(Uint16 xPos, Uint16 yPos) {
        this->xPos = xPos; 
        this->yPos = yPos; 
    }

    void resize(Uint16 width, Uint16 height) { 
        this->width = width;
        this->height = height;
    }

    // Window Dimensions Getters
    Uint16 getWidth() { return width; }
    Uint16 getHeight() { return height; }

    // Window Flag Toggles
    void toggleFullScreen() { windowFlags ^= SDL_WINDOW_FULLSCREEN; }
    void toggleHighDPI() { windowFlags ^= SDL_WINDOW_ALLOW_HIGHDPI; }
    void toggleResizeable() { windowFlags ^= SDL_WINDOW_RESIZABLE; }
    void toggleBorders() { windowFlags ^= SDL_WINDOW_BORDERLESS; }

    // Renderer Flag Toggles
    void toggleSoftwareRender() { _render_flags ^= SDL_RENDERER_SOFTWARE; }
    void toggleHardwareRender() { _render_flags ^= SDL_RENDERER_ACCELERATED; }
    void toggleVSync() { _render_flags ^= SDL_RENDERER_PRESENTVSYNC; } 
    void toggleToTexture() { _render_flags ^= SDL_RENDERER_TARGETTEXTURE; }

    // Window Flag Getters
    bool isFullScreen() { return ((windowFlags&SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN); }
    bool isHighDpi() { return ((windowFlags&SDL_WINDOW_ALLOW_HIGHDPI) == SDL_WINDOW_ALLOW_HIGHDPI); }
    bool isResizeable() { return ((windowFlags&SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE); }

    // For Making a renderer
    SDL_Window *get_SDL_Window() {return sdlWindow;}

    // Drawing and Clearing
    bRenderer *createWindow();
    
    void setWindowTitle(const char *title) { SDL_SetWindowTitle(sdlWindow, title); }

    void closeWindow();

private:

    SDL_Window* sdlWindow;
    bRenderer *_renderer;

    const char *windowTitle;

    // Not a bRect because Uint16 is good enough :3
    Uint16 xPos;
    Uint16 yPos;

    Uint16 width;
    Uint16 height;

    Uint32 windowFlags = 0;
    Uint32 _render_flags = 0;

};

#endif
