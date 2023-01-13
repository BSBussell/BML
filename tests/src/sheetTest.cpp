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
    sprite.width = 800;
    sprite.height = 800;
    
    spriteSheet.imagePath = path;
    spriteSheet.totalWidth = 1601;
    spriteSheet.totalHeight = 2397;

    spriteSheet.sprites.push_back(sprite);

    sprite.x = 800;
    spriteSheet.sprites.push_back(sprite);

    spriteSheet.totalSprites = 2;

    writeSheetToBin(BML_GetPath("../resources/spriteSheet.dat").c_str(), spriteSheet);

    // Step 2: Make sure we are reading in the data correctly
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

    printf("At this point the reading and writing of Spritesheets is working\n");


    // Step 3 Test printing the Sheet
    //readSheet.currentSprite = 0;

    bool run = true;

    BML_Init();
    bWindow* window = new bWindow("Sprite Sheet Test", 0, 0, 1600, 900);
    
    // Ok looking at this a year after I developed this, I hate it
    // This should be something that should be set, like maybe a bool?
    // However now that I've peaked at bit more at this function... I get it a bit more...
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->toggleVSync();
    window->toggleHighDPI();


    window->createWindow();

    bRect dest = {10,10,800,800};
   
    if (!bSound::openAudio())
        printf(":(");

    //  bSound music;
    bSound::loadMUS("../resources/BLUE-Compress.wav");
    bSound::playMUS(5);

    // I think this should be something handled in the sheet function
    window->initSpriteSheet(readSheet);

    while(run) {

        

        // Event loop
        run = bEvent::eventLoop();

        if (bEvent::keyDown('W')) {
            dest.y--;
        } 
        if (bEvent::keyDown('S')) {
            dest.y++;
        }
        if (bEvent::keyDown('A')) {
            dest.x--;
        }
        if (bEvent::keyDown('D')) {
            dest.x++;
        }
        if (bEvent::keyDown('q')) {
            readSheet.currentSprite ^= 1;
            run = false;
        }
        window->drawSprite(readSheet, dest);
        window->drawRect(dest, 0, 255, 0);

        window->drawBuffer();
    }
    bSound::freeMUS();
    bSound::closeAudio();
    window->closeWindow();
    BML_Close();

    return 0;
}
