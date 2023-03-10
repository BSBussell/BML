
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

// @brief Data structure used for storing texture info
struct bTexture {


	std::string path;

	SDL_Texture *texture;
	SDL_Rect src;

};

// @brief Class for mananging usage of textures
class bTextureManager {

public:

	bTextureManager(SDL_Renderer *renderer);
	~bTextureManager();

	// Load the texture either by creating a new one or grabbing it from the cache
	bTexture loadTexture(const char *path, bRect dim);

	// Unloads the texture, if it's not being used by anything else
	void unloadTexture(bTexture texture);

	// Does not delete bTextures, User still has to do that on ther own
	void clearCache();

	// Rendering the Texture either using a rect or a point
	void renderTexture(bTexture &texture, bRect dest);
	void renderTexture(bTexture &texture, bPoint dest);
	

private:

	SDL_Renderer *_sdl_renderer;

	// Cache
	std::unordered_map<std::string, SDL_Texture*> _loaded_textures;
	std::unordered_map<SDL_Texture*, Uint8> _refs;

};

#endif
