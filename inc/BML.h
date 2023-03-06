
#ifndef BML_H
#define BML_H

#include <string>
#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "bRect.h"
#include "bTexture.h"
#include "bSheet.h"
#include "bEvent.h"
#include "bWindow.h"
#include "bSound.h"

void BML_Init();
void BML_Close();

std::string BML_GetPath(const char* path);
std::string BML_GetPath(std::string path);

#endif
