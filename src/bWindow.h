
// Bee Bussell
// Sept 1, 2021
// Header

#ifndef bWindow_h
#define bWindow_h

#include <SDL2/SDL.h>
#include <stdint.h>

#endif

class bWindow {

public:

    bWindow(const char *windowTitle, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height)
        : windowTitle(windowTitle)
        , xPos(xPos)
        , yPos(yPos)
        , width(width)
        , height(height)
    { }
    ~bWindow();

    void move(uint16_t xPos, uint16_t yPos) { 
        this->xPos = xPos; 
        this->yPos = yPos; 
    }

    void resize(uint16_t width, uint16_t height) { 
        this->width = width;
        this->height = height;
    }

    void toggleFullScreen() { flags ^= SDL_WINDOW_FULLSCREEN; }

    void toggleHighDPI() { flags ^= SDL_WINDOW_ALLOW_HIGHDPI; }
    void toggleResizeable() { flags ^= SDL_WINDOW_RESIZABLE; }
    void toggleBorders() { flags ^= SDL_WINDOW_BORDERLESS; }

    bool readFullScreen() { return ((flags&SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN); }
    bool readHighDpi() { return ((flags&SDL_WINDOW_ALLOW_HIGHDPI) == SDL_WINDOW_ALLOW_HIGHDPI); }
    bool readResizeable() { return ((flags&SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE); }

    void createWindow();
    void clearBuffer() { SDL_RenderClear(sdlRenderer); }
    void updateBuffer() { SDL_RenderPresent(sdlRenderer); }


    uint16_t getWidth() { return width; }
    uint16_t getHeight() { return height; }

private:

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;

    const char *windowTitle;

    uint16_t xPos;
    uint16_t yPos;

    uint16_t width;
    uint16_t height;

    uint32_t flags;

};

