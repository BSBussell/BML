// Bee Bussell
// Sep 8, 2021
// For Later

#include "bTexture.h"
#include "BML.h"

bTextureManager::bTextureManager(SDL_Renderer *renderer) {

	_sdl_renderer = renderer;
}

bTextureManager::~bTextureManager() {

	clearCache();
}

// Load the texture either by creating a new one or grabbing it from the cache
bTexture bTextureManager::loadTexture(const char *path, bRect dim) {

	std::string absPath = BML_GetPath(path);

	// No matter what we're make a new bTexture
	bTexture newTexture;// = new bTexture();
	newTexture.src = dim;
	newTexture.path = absPath;

	// If we've already loaded this image
	auto iter = _loaded_textures.find(absPath);
	if (iter != _loaded_textures.end()) {

		// Setup 
		newTexture.texture = iter -> second;

		// Increase the ref count
		auto refs_iter = _refs.find(iter -> second);
		refs_iter -> second++;

		return newTexture;
	}

	// Create new texture
	SDL_Surface* surface = IMG_Load(absPath.c_str());
    newTexture.texture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);
    SDL_FreeSurface(surface);

    // Setup our look ups and reference counter
    _loaded_textures[absPath] = newTexture.texture;
    _refs[newTexture.texture] = 1;

    return newTexture;
}

// Kinda do the opposite of the above
void bTextureManager::unloadTexture(bTexture texture) {

	// Decrease the ref count
	auto refs_iter = _refs.find(texture.texture);
	
	// If it's not in the map just delete the bTexture
	if (refs_iter == _refs.end()) {
		//delete texture;
		return;
	}

	refs_iter->second--;

	// If the ref count is zero, delete it from the cache and free memory
	if (refs_iter->second == 0) {
		auto loaded_iter = _loaded_textures.find(texture.path);
		if (loaded_iter != _loaded_textures.end()) {
			SDL_DestroyTexture(loaded_iter->second);
			_loaded_textures.erase(loaded_iter);
		}
		_refs.erase(refs_iter);
	}

}

// Clear the maps and free all memory, extremely dangerous to use,,, please be careful
void bTextureManager::clearCache() {

	// Delete all loaded textures and reset the reference counters
	for (auto& texture : _loaded_textures) {
		SDL_DestroyTexture(texture.second);
	}
	_loaded_textures.clear();
	_refs.clear();

}

void bTextureManager::renderTexture(bTexture &texture, bRect dest) {

	// Make sure the SDL_Texture hasn't been unloaded
	auto refs_iter = _refs.find(texture.texture);
	if (refs_iter == _refs.end()) {

		// Create new texture
		SDL_Surface* surface = IMG_Load(texture.path.c_str());
	    texture.texture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);
	    SDL_FreeSurface(surface);

	    // Setup our look ups and reference counter
	    _loaded_textures[texture.path] = texture.texture;
	    _refs[texture.texture] = 1;	
	}

	// I could not find an easy way around doing this ngl
	SDL_Rect SDL_dest = SDL_Rect(dest); 

	SDL_RenderCopy(_sdl_renderer, texture.texture, &texture.src, &SDL_dest);
}

void bTextureManager::renderTexture(bTexture &texture, bPoint dest) {

	// Make sure the SDL_Texture hasn't been unloaded
	auto refs_iter = _refs.find(texture.texture);
	if (refs_iter == _refs.end()) {

		// Create new texture
		SDL_Surface* surface = IMG_Load(texture.path.c_str());
	    texture.texture = SDL_CreateTextureFromSurface(_sdl_renderer, surface);
	    SDL_FreeSurface(surface);

	    // Setup our look ups and reference counter
	    _loaded_textures[texture.path] = texture.texture;
	    _refs[texture.texture] = 1;	
	}

	// I could not find an easy way around doing this ngl
	SDL_Rect SDL_dest = {(int)dest.x, (int)dest.y, texture.src.w, texture.src.h}; 
	SDL_RenderCopy(_sdl_renderer, texture.texture, &texture.src, &SDL_dest);
}
