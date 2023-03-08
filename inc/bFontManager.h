
// Bee Bussell
// March 6, 2023
// bFontManager.h

#ifndef B_FONT_MANAGER_H
#define B_FONT_MANAGER_H

#include <string>
#include <unordered_map>
#include <SDL2/SDL_ttf.h>

#include "bRect.h"

class bFontManager;

// The Font Data Only can be managed by bFontManager
class bFont {

	bFont(std::string font_path, Uint8 font_size, SDL_Color color);
	~bFont();

    TTF_Font* _font;
    Uint8 _size;

    SDL_Color _color;

    // Let Font Manager be the only one who makes this
    friend class bFontManager;

};

class bFontManager {
public:

    bFontManager(SDL_Renderer* renderer);
    ~bFontManager();

    // Loading Font's in and out
    void loadFont(const std::string &font_path, Uint8 font_size);
    void unloadFont(const std::string &font_path, Uint8 font_size);

    // Setting the current font
    void setFont(const std::string &font, Uint8 font_size, SDL_Color color);

    // Render the font
    void render(std::string text, bPoint position);

private:

	bFont* _currentFont;
    SDL_Renderer* _renderer;

    std::unordered_map<std::string, bFont*> _fonts;
    std::unordered_map<bFont*, std::string> _keys;
};



#endif