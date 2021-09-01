
// Bee Bussell
// Sept 1, 2021
// Header

#ifndef bWindow_h
#define bWindow_h

#include <SDL2/SDL.h>
#include <stdint.h>

class bWindow {

public:

    bWindow();
    ~bWindow();

    void move(uint16_t xPos, uint16_t yPos);
    void resize(uint16_t width, uint16_t height);

    void toggleFullScreen() { flags ^= SDL_WINDOW_FULLSCREEN; }

    void toggleHighDPI() { flags ^= SDL_WINDOW_ALLOW_HIGHDPI; }
    void toggleResizeable() { flags ^= SDL_WINDOW_RESIZABLE; }
    void toggleBorders() { flags ^= SDL_WINDOW_BORDERLESS; }

    bool readFullScreen() { return ((flags&SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN); }
    bool readHighDpi() { return ((flags&SDL_WINDOW_ALLOW_HIGHDPI) == SDL_WINDOW_ALLOW_HIGHDPI); }
    bool readResizeable() { return ((flags&SDL_WINDOW_RESIZABLE) == SDL_WINDOW_RESIZABLE); }

    void createWindow();

    uint16_t getWidth();
    uint16_t getHeight();

private:

    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer

    char *windowTitle;

    uint16_t xPos;
    uint16_t yPos;

    uint16_t width;
    uint16_t height;

    uint32_t flags;

};

