
// Bee Bussell
// Sept 6, 2021
// bTexture/manager

#ifndef BML_TEXTURE_H
#define BML_TEXTURE_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "bRect.h"

struct bTexture {

	~bTexture();

	std::string path;

	SDL_Texture *texture;
	SDL_Rect src;

};

class bTextureManager {

public:

	bTextureManager(SDL_Renderer *renderer);
	~bTextureManager();

	/* 
		Ok so load_texture will check the path with _loaded_textures,
		if it finds that it has loaded it already it will
		Make a new bTexture with the src, copy the SDL_Texture from
		_loaded_textures increment the _refs value keyed on the texture
		and return it.
		Otherwise, completely make a new texture setup the slot in _refs 
		and _loaded_textures
	*/

	bTexture loadTexture(const char *path, bRect dim);
	void unloadTexture(bTexture texture);

	// Does not delete bTextures, User still has to do that on ther own
	void clearCache();

	void renderTexture(bTexture &texture, bRect dest);

private:

	SDL_Renderer *_sdl_renderer;


	std::unordered_map<std::string, SDL_Texture*> _loaded_textures;
	std::unordered_map<SDL_Texture*, Uint8> _refs;

	//std::unordered_map<SDL_Texture*, bTexture*> _b_textures;

};

#endif
