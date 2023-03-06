// Bee Bussell
// Sept 17, 2022
// Testing animation class creator.

#include <iostream>
#include <string>
#include <stdint.h>
#include <BML/BML.h>

int main() {
 
    // Run diff to check for differences
    
        
    bool run = true;
    
    BML_Init();

    bSheet spriteSheet;
    readSheetFromJSON(BML_GetPath("../resources/NoelAssets/MCaniHIGH-Start_walk.json").c_str(), spriteSheet);
    spriteSheet.startAnimation("default");
    
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
