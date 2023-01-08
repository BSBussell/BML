
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

struct bSheet {

    std::string imagePath;
    bTexture sourceTexture;

    uint32_t totalWidth;
    uint32_t totalHeight;

    uint16_t totalSprites;
    uint16_t currentSprite = 0;

    std::vector<bRect> sprites;

};

void writeSheetToBin(const char* filePath, bSheet data);
bool readSheetFromBin(const char* filePath, bSheet &data);

#endif
