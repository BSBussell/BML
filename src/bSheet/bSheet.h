
// Bee Bussell
// Sept 14, 2021
// bSheet Header File

#ifndef bSheet_h
#define bSheet_h

#include "bData/bRect.h"
#include "bTexture/bTexture.h"
#include <fstream>
#include <stdint.h>
#include <vector>

/// @brief Datastructure used for information about an animation
struct bAnimation {

    std::vector<uint16_t> frames;

    uint16_t frameIndex;
    // How often to update animations
    uint32_t animationSpeed;
    uint64_t tickCount;
};

/// @brief Data structure used for storing spritesheet info
struct bSheet {

    std::string imagePath;
    bTexture sourceTexture;

    bool animated = false;

    uint32_t totalWidth;
    uint32_t totalHeight;

    uint16_t totalSprites;
    uint16_t currentSprite = 0;

    std::vector<bRect> sprites;

    // Maybe make this like a dictionary that can be added to or something
    bAnimation *currentAnimation = NULL;
    std::vector<bAnimation> animations;

    bool startAnimation(uint16_t animation);
    bool updateAnimation();
    bool stopAnimation();

};

void writeSheetToBin(const char* filePath, bSheet data);
bool readSheetFromBin(const char* filePath, bSheet &data);

#endif
