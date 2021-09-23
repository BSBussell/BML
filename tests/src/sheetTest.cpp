// Bee Bussell
// Sept 17, 2021
// Testing sheet class creator.

#include <iostream>
#include <string>
#include <stdint.h>
#include <BML/BML.h>

int main() {

   
    // Step 1: Make sure reading and writing .dat files works

    bRect sprite;
    std::string path = "../resources/spriteSheet.png";

    bSheet spriteSheet;

    sprite.x = 0;
    sprite.y = 0;
    sprite.width = 10;
    sprite.height = 10;
    
    spriteSheet.imagePath = path;
    spriteSheet.totalWidth = 1601;
    spriteSheet.totalHeight = 2397;

    spriteSheet.sprites.push_back(sprite);

    sprite.x = 10;
    spriteSheet.sprites.push_back(sprite);

    spriteSheet.totalSprites = 2;

    writeSheetToBin(BML_GetPath("../resources/spriteSheet.dat").c_str(), spriteSheet);

    bSheet readSheet;
    readSheetFromBin(BML_GetPath("../resources/spriteSheet.dat").c_str(), readSheet);

    printf("Image Path: %s\n", readSheet.imagePath.c_str());
    printf("Total Width: %i\n", readSheet.totalWidth);
    printf("Total Height: %i\n", readSheet.totalHeight);
    printf("Total Sprites: %i\n", readSheet.totalSprites);

    for (bRect vals: readSheet.sprites) {

        printf("Rect-----\n");
        printf("X: %i\n", vals.x);
        printf("Y: %i\n", vals.y);
        printf("Width: %i\n", vals.width);
        printf("Height: %i\n", vals.height);
        printf("------\n");
    }



    return 0;
}
