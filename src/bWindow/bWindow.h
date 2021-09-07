
// Bee Bussell
// Sept 1, 2021
// Header

#ifndef bWindow_h
#define bWindow_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include "../bData/bRect.h"
#include "../bTexture/bTexture.h"

class bWindow {

public:

    // Constructors and Destroyer
    bWindow(const char *windowTitle, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height)
        : windowTitle(windowTitle)
        , xPos(xPos)
        , yPos(yPos)
        , width(width)
        , height(height)
    { }
    ~bWindow();

    // Window Dimensions and Position Setters
    void move(uint16_t xPos, uint16_t yPos) {
        this->xPos = xPos; 
        this->yPos = yPos; 
    }

    void resize(uint16_t width, uint16_t height) { 
        this->width = width;
        this->height = height;
    }

    // Window Dimensions Getters
    uint16_t getWidth() { return width; }
    uint16_t getHeight() { return height; }

    // Window Flag Toggles
    void toggleFullScreen() { windowFlags ^= SDL_WINDOW_FULLSCREEN; }
    void toggleHighDPI() { windowFlags ^= SDL_WINDOW_ALLOW_HIGHDPI; }
    void toggleResizeable() { windowFlags ^= SDL_WINDOW_RESIZABLE; }
    void toggleBorders() { windowFlags ^= SDL_WINDOW_BORDERLESS; }

    // Window Flag Getters
    bool isFullScreen() { return ((windowFlags&SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN); }
    bool isHighDpi() { return ((windowFlags&SDL_WINDOW_ALLOW_HIGHDPI) == SDL_WINDOW_ALLOW_HIGHDPI); }
    bool isResizeable() { return ((windowFlags&SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE); }

    // Renderer Flag Toggles
    void toggleSoftwareRender() { renderFlags ^= SDL_RENDERER_SOFTWARE; }
    void toggleHardwareRender() { renderFlags ^= SDL_RENDERER_ACCELERATED; }
    void toggleVSync() { renderFlags ^= SDL_RENDERER_PRESENTVSYNC; } 
    void toggleToTexture() { renderFlags ^= SDL_RENDERER_TARGETTEXTURE; }

    // Drawing and Clearing
    bool createWindow();
    void clearBuffer() { SDL_RenderClear(sdlRenderer); }
    void updateBuffer() { SDL_RenderPresent(sdlRenderer); }

    // Initalize Textures
    bTexture initTexture(const char* source, bRect src);

    // Drawing Textures and Rectangles
    void drawTexture(bTexture texture, bRect dest);
    void drawTexture(const char* source, bRect src, bRect dest);
    void drawRect(bRect location, uint8_t r, uint8_t g, uint8_t b);

    void closeWindow();

private:

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;

    const char *windowTitle;

    uint16_t xPos;
    uint16_t yPos;

    uint16_t width;
    uint16_t height;

    uint32_t windowFlags = 0;
    uint32_t renderFlags = 0;

    inline static uint8_t numOfWindows;

};

#endif
