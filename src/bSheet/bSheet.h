
// Bee Bussell
// Sept 14, 2021
// bSheet Header File

#ifndef bSheet_h
#define bSheet_h

#include "BML/BML.h"
#include <fstream>
#include <stdint.h>
#include <vector>


#pragma pack(push, 1)
struct bSheet {

    std::string imagePath;
    bTexture sourceTexture;

    uint32_t totalWidth;
    uint32_t totalHeight;

    std::vector<bRect> sprites;
};
#pragma pack(pop)


/* MOVE THIS TO CPP */
void writeSheetToBin(const char* filePath, bSheet data);

#endif
