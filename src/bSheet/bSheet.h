
// Bee Bussell
// Sept 14, 2021
// bSheet Header File

#ifndef bSheet_h
#define bSheet_h

#include "bData/bRect.h"
#include "bTexture/bTexture.h"
#include <fstream>
#include <stdint.h>
#include <queue>
#include <unordered_map>

#include "../../include/json.hpp"
using json = nlohmann::json;

/* 
    You can really tell how most of this was written after I 
    spent a semester taking a class that restricted me to only
    using C :3
*/ 


/// @brief Datastructure used for information about an animation
struct bAnimation {

    std::queue<uint16_t> frames;
    std::queue<uint32_t> duration;

    std::string name;

    // How often to update animations
    //uint32_t speed;
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
    std::unordered_map<std::string, bAnimation> animations;

    bool startAnimation(std::string key);

    // PLEASE BEE IM BEGGING YOU DO NOT USE THIS!!!
    bool startAnimation(bAnimation *animation);

    bool updateAnimation();
    bool stopAnimation();

};

//void writeSheetToBin(const char* filePath, bSheet data);
bool readSheetFromJSON(const char* filePath, bSheet &data);

#endif
