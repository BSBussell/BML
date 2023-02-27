
#ifndef BML_h
#define BML_h

#include <string>
#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "bData/bRect.h"
#include "bTexture/bTexture.h"
#include "bSheet/bSheet.h"
#include "bEvent/bEvent.h"
#include "bWindow/bWindow.h"
#include "bSound/bSound.h"

void BML_Init();
void BML_Close();

std::string BML_GetPath(const char* path);
std::string BML_GetPath(std::string path);

#endif
