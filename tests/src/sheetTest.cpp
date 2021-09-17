// Bee Bussell
// Sept 17, 2021
// Testing sheet class creator.

#include <iostream>
#include <string>
#include <stdint.h>
#include <BML/BML.h>

int main() {

    
    bRect sprite;
    std::string path = "../resources/spriteSheet.png";

    bSheet spriteSheet;

    sprite.x = 0;
    sprite.y = 0;
    sprite.width = 10;
    sprite.height = 10;
    
    spriteSheet.imagePath = path;
    spriteSheet.totalWidth = 50;
    spriteSheet.totalHeight = 50;

    spriteSheet.sprites.push_back(sprite);

    sprite.x = 10;
    spriteSheet.sprites.push_back(sprite);

    spriteSheet.totalSprites = 2;

    writeSheetToBin(BML_GetPath("../resources/spriteSheet.dat").c_str(), spriteSheet);


    return 0;
}
