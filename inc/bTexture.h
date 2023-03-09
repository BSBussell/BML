
// Bee Bussell
// Sept 6, 2021
// Header

#ifndef BML_TEXTURE_H
#define BML_TEXTURE_H

//#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>

// Just a header file for now

struct bTexture {

	std::string path;

	SDL_Texture* texture;
	SDL_Rect src;
};

class bTextureManager {

public:

	bTextureManager(SDL_Renderer renderer);
	~bTextureManager();

	/* 
		Ok so load_texture will check the path with loaded_textures,
		if it finds that it has loaded it already it will
		Make a new bTexture with the src, copy the SDL_Texture and return it
		Otherwise, 
	*/
	bTexture *loadTexture(const char *path, bRect dim);
	void unloadTexture(bTexture *texture);

	void clearCache();

private:

	SDL_Renderer *_sdl_renderer;

	std::unordered_map<std::string, SDL_Texture*> _loaded_textures;
	std::unordered_map<SDL_Texture*, Uint8> _refs;
}

#endif
