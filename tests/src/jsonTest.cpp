// Bee Bussell
// Sept 17, 2022
// Testing animation class creator.

#include <iostream>
#include <string>
#include <stdint.h>
#include <BML/BML.h>

int main() {

   
    // Step 1: Make sure reading and writing .dat files works
    /*
    bRect sprite;
    std::string path = "../resources/SpriteSheet2.png";

    bSheet spriteSheet;

    sprite.x = 0;
    sprite.y = 0;
    sprite.width = 8;
    sprite.height = 8;
    
    spriteSheet.imagePath = path;
    spriteSheet.totalWidth = 56;
    spriteSheet.totalHeight = 8;

    spriteSheet.sprites.push_back(sprite);

    // Making the 8 sprites we need
    for (int i = 1; i < 7; i++ ) {
        sprite.x += 8;
        spriteSheet.sprites.push_back(sprite);
    }

    spriteSheet.totalSprites = 7;

    */
    // Step 2: Make sure we are reading in the data correctly
    // bAnimation full;
    // full.name = "Cycle";
    // for (int i = 0; i < 7; i++)
    //     full.frames.push(i);
    // full.speed = 200;
    // spriteSheet.animations["Cycle"] = full;

    
    //writeSheetToBin(BML_GetPath("../resources/spriteSheet2.dat").c_str(), spriteSheet);
    

    // This is some ugly ass implementation right here clean this later :3
    //spriteSheet.startAnimation("Cycle");
    
    // Run diff to check for differences
    bSheet spriteSheet;
    readSheetFromJSON(BML_GetPath("../resources/NoelAssets/MCaniHIGH-Start_walk.json").c_str(), spriteSheet);
    spriteSheet.startAnimation("defaultAseprite");

    printf("Image Path: %s\n", spriteSheet.imagePath.c_str());
    printf("Total Width: %i\n", spriteSheet.totalWidth);
    printf("Total Height: %i\n", spriteSheet.totalHeight);
    printf("Total Sprites: %i\n", spriteSheet.totalSprites);

    for (bRect vals: spriteSheet.sprites) {

        printf("-----Rect-----\n");
        printf("X: %i\n", vals.x);
        printf("Y: %i\n", vals.y);
        printf("Width: %i\n", vals.width);
        printf("Height: %i\n", vals.height);
        printf("--------------\n");
    }


    // Step 3 Test printing the Sheet
    //spriteSheet.currentSprite = 0;
    
    
    bool run = true;
    
    BML_Init();
    
    bWindow* window = new bWindow("JSON Test", 0, 0, 800, 450);
    
    // Ok looking at this a year after I developed this, I hate it
    // This should be something that should be set, like maybe a bool?
    // However now that I've peaked at bit more at this function... I get it a bit more...
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->toggleVSync();
    window->toggleHighDPI();

    window->createWindow();
    
    bRect dest = {10,10,128,128};
    
    if (!bSound::openAudio())
        printf(":(");

    //  bSound music;
    bSound::loadMUS("../resources/BLUE-Compress.wav");
    bSound::playMUS(5);

    
    // I think this should be something handled in the sheet function
    window->initSpriteSheet(spriteSheet);
    
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
        if (bEvent::keyDown('Q')) {
            run = false;
        }
        window->drawRect(dest, 255, 255, 255);
        window->drawSprite(spriteSheet, dest);
        

        window->drawBuffer();
        //run = false;
    }
    spriteSheet.stopAnimation();
    //
    window->freeSpriteSheet(spriteSheet);
    
    bSound::freeMUS();
    bSound::closeAudio();
    
    window->closeWindow();
    
    BML_Close();
    
    return 0;
}
