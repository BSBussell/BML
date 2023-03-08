
// Bee Bussell
// March 6 2023
// bFontManager.cpp

#include "bFontManager.h"
#include "BML.h"

bFont::bFont(std::string font_path, Uint8 font_size, SDL_Color color) {

	//bFont *font = new bFont();
    _size = font_size;
    _font = TTF_OpenFont(font_path.c_str(), font_size);
    _color = color;
}

bFont::~bFont() {

	TTF_CloseFont(_font);	
}

// Creating our Font Manager, initializes TTF
bFontManager::bFontManager(SDL_Renderer* renderer) {
	
	_renderer = renderer;
	TTF_Init();
}

// Destroying our Font Manager
bFontManager::~bFontManager() {


	// Remove all Loaded fonts
	for (auto& font : _fonts) {
        
        // Free Memory
        delete font.second;
    }

    // Shut down font engine :3
    TTF_Quit();
}

// Loading a Font into our map
void bFontManager::loadFont(const std::string& font_path, Uint8 font_size) {

	std::string abs_font_path = BML_GetPath(font_path);
	std::string font_key = abs_font_path + "_" + std::to_string(font_size);

	if (_fonts.find(font_key) != _fonts.end()) {
        return;
    }

    // Create our font
    bFont *font = new bFont(
        abs_font_path, 
        font_size, 
        {255,255,255,255}
    );
    

    if (!font -> _font) {
        
        perror("Font Could Not Be Found\n");
        fprintf(stderr, "Path: %s\n", abs_font_path.c_str());
        exit(1);
    }

    _fonts[font_key] = font;
    _keys[font] = font_key;
}

void bFontManager::unloadFont(const std::string& font_path, Uint8 font_size) {

	std::string abs_font_path = BML_GetPath(font_path);
	std::string font_key = abs_font_path + "_" + std::to_string(font_size);

	// Reverse Lookup :3
	auto iter = _fonts.find(font_key);
	if (iter != _fonts.end()) {
        
        // Call fonts destructer
        delete iter -> second;

        // Close the font and erase elements
        _fonts.erase(iter -> first);
        return;
    
    }
}

// Sets the font
void bFontManager::setFont(const std::string &font_path, Uint8 font_size, SDL_Color color = {255, 255, 255, 255}) {

	std::string abs_font_path = BML_GetPath(font_path);
	std::string font_key = abs_font_path + "_" + std::to_string(font_size);	

	auto iter = _fonts.find(font_key);

	// If the font described is missing load it
	if (iter == _fonts.end()) {

		loadFont(font_path, font_size);

		// I don't like calling find to look for an element we just created
		iter = _fonts.find(font_key);
	}

	bFont *font = iter -> second;

	font -> _color = color;

	_currentFont = font;
}


// Renders using the current font at the given position
void bFontManager::render(std::string text, bPoint position) {

    // Create a surface from the text using the font and size
    SDL_Surface* surface = TTF_RenderText_Solid(_currentFont -> _font, text.c_str(), _currentFont -> _color);

    // Create a texture from the surface using the renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);

    // Set the position and size of the texture
    SDL_Rect rect = {
    	(int)position.x, (int)position.y, 
    	surface->w, surface->h
    };

    // Render the texture to the renderer
    SDL_RenderCopy(_renderer, texture, NULL, &rect);

    // Clean up the surface and texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}