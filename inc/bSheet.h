
// Bee Bussell
// Sept 14, 2021
// bSheet Header File

#ifndef BML_SHEET_H
#define BML_SHEET_H


//#include "BML.h"
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
 
    // @brief The path to the spritesheet
    std::string imagePath;

    // @brief The bTexture of the spritesheet
    bTexture sourceTexture;

    // @brief Whether or not the sheet is animated
    bool animated = false;

    // @brief The total width of the source texture
    Uint32 totalWidth;

    // @brief The total height of the source texture
    Uint32 totalHeight;

    // @brief The total amount of sprites in the sheet
    Uint16 totalSprites;


    // @brief The current sprite being displayed
    uint16_t currentSprite = 0;

    // @brief The rectangles for each sprite
    std::vector<bRect> sprites;

    // @brief The current animation being played as a pointer
    bAnimation *currentAnimation = NULL;

    // @brief All the animations in the sheet, keyed on their name
    std::unordered_map<std::string, bAnimation> animations;

    /**
     * @brief Starts the animation with the given key
     * 
     * @param std::string the key to check the map for
     * @return True if it found the key 
     * @return False if it didn't find the key
     */
    bool startAnimation(std::string key);

    /**
     * @brief Starts the animation from the given pointer, don't use this
     * 
     * @param animation 
     * @return true 
     * @return false 
     */
    bool startAnimation(bAnimation *animation);

    /**
     * @brief Updates the animation, used internally
     * 
     * @return true 
     * @return false 
     */
    bool updateAnimation();

    /**
     * @brief Stops the animation
     * 
     * @return true 
     * @return false 
     */
    bool stopAnimation();

};


/**
 * @brief Reads a spritesheet from a Aseprite JSON file
 * 
 * @param filePath 
 * @param data 
 * @return true 
 * @return false 
 */
bool readSheetFromJSON(const char *filePath, bSheet &data);

/**
 * @brief Gets the tick count
 *
 */
Uint64 BML_GetTicks();

#endif
