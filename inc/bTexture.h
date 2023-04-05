
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

// TODO: Implement texture freeing and destructer for that

// @brief Data structure used for storing texture info
struct bTexture {


	std::string path;

	SDL_Texture *texture;
	SDL_Rect src;

};

/**
 * @brief A class for managing textures in a cache
 * 
 */
class bTextureManager {

public:

	/**
	 * @brief Making a bTextureManager tied to the renderer
	 * 
	 * @param SDL_Renderer* renderer 
	 */
	bTextureManager(SDL_Renderer *renderer);

	/**
	 * @brief Destroy the b Texture Manager::b Texture Manager object by clearing the cache
	 * 
	 */
	~bTextureManager();

	/**
	 * @brief Load the texture either by creating a new one or grabbing it from the cache
	 * 
	 * @param const_char* the path to the texture
	 * @param bRect the dimensions of the texture
	 */
	bTexture loadTexture(const char *path, bRect dim);

	/**
	 * @brief Unload the texture by decreasing the ref count and deleting it if it's at zero
	 * 
	 * @param bTexture the texture to unload
	 */
	void unloadTexture(bTexture texture);

	/**
	 * @brief Clear the cache of textures
	 * 
	 */
	void clearCache();

	/**
	 * @brief Render the texture to the screen
	 * 
	 * @param bTexture the texture to render
	 * @param bRect the destination rectangle
	 */
	void renderTexture(bTexture &texture, bRect dest);

	/**
	 * @brief Render the texture to the screen
	 * 
	 * @param bTexture the texture to render
	 * @param bPoint the destination point
	 */
	void renderTexture(bTexture &texture, bPoint dest);
	

private:

	/**
	 * @brief The renderer that the textures are tied to
	 */
	SDL_Renderer *_sdl_renderer;

	
	/**
	 * @brief Cache of allocated textures
	 */
	std::unordered_map<std::string, SDL_Texture*> _loaded_textures;

	/**
	 * @brief Reference counter for textures
	 */
	std::unordered_map<SDL_Texture*, Uint8> _refs;



};

#endif
