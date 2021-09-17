
// Bee Bussell
// Sept 14, 2021
// bSheet Header File

#ifndef bSheet_h
#define bSheet_h

#include "BML/BML.h"
#include <fstream>
#include <stdint.h>
#include <vector>

struct bSheet {

    std::string imagePath;
    bTexture sourceTexture;

    uint32_t totalWidth;
    uint32_t totalHeight;

    uint16_t totalSprites;

    std::vector<bRect> sprites;
};

void writeSheetToBin(const char* filePath, bSheet data);
bool readSheetFromBin(const char* filePath, bSheet &data);

#endif
