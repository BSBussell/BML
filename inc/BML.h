
#ifndef BML_H
#define BML_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "bRect.h"
#include "bTexture.h"
#include "bSheet.h"
#include "bEvent.h"
#include "bFontManager.h"
#include "bRenderer.h"
#include "bWindow.h"
#include "bSound.h"

/**
 * @brief Initializes SDL
 * 
 */
void BML_Init();

/**
 * @brief Closes SDL
 * 
 */
void BML_Close();

/**
 * @brief Gets the path to the file
 * 
 * @param const char* relative path to the file
 * @return std::string absolute path to the file
 */
std::string BML_GetPath(const char* path);

/**
 * @brief Gets the path to the file
 * 
 * @param std::string path relative path to the file 
 * @return std::string Absolute path to the file
 */
std::string BML_GetPath(std::string path);

/**
 * @brief Gets the tick count
 *
 */
// Uint64 BML_GetTicks();

#endif
