
// Bee Bussell
// Sept 14, 2021
// bSheet Header File

#ifndef BML_SHEET_H
#define BML_SHEET_H

#include "bRect.h"
#include "bTexture.h"

#include <fstream>
#include <stdint.h>
#include <queue>
#include <string>
#include <unordered_map>

#include "json.h"
using json = nlohmann::json;

/* 
    You can really tell how most of this was written after I 
    spent a semester taking a class that restricted me to only
    using C :3
*/ 


// @brief Datastructure used for information about an animation
struct bAnimation {

    std::queue<Uint16> frames;
    std::queue<Uint32> duration;

    std::string name;

    // How often to update animations
    //Uint32 speed;
    Uint64 tickCount;
};

// @brief Data structure used for storing spritesheet info
struct bSheet {
 
    std::string imagePath;
    bTexture sourceTexture;

    bool animated = false;

    Uint32 totalWidth;
    Uint32 totalHeight;

    Uint16 totalSprites;
    Uint16 currentSprite = 0;

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
bool readSheetFromJSON(const char *filePath, bSheet &data);

#endif
