
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented events :3

#include <iostream>
#include <stdint.h>
#include <bSDL/bSDL.h>


int main() {

    bool run = true;

    bWindow* window = new bWindow("silly", 0, 0, 1600, 900);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->toggleVSync();
    window->createWindow();

    bRect dest = {10,10,320,240};
    bRect src = {10,10,320,240};
   
    if (!bSound::openAudio())
        printf(":(");

    bSound soundEffect;
    soundEffect.loadSFX("../resources/randomSound.wav");
    soundEffect.playSFX(0,2);
  //  bSound music;
    bSound::loadMUS("../resources/BLUE-Compress.wav");
    bSound::playMUS(5);

    //bTexture blueSquare = window->initTexture("/home/bee/Development/bSDL/tests/resources/blueSquare.png", src);
    bTexture blueSquare = window->initTexture("../resources/blueSquare.png", src);
    
    while(run) {

        window->clearBuffer();

        // Event loop
        run = bEvent::eventLoop();

        if (bEvent::keyDown('W')) {
            dest.y--;
        } 
        if (bEvent::keyDown('S')) {
            dest.y++;
        }
        if (bEvent::keyDown('A'))
            dest.x--;
        if (bEvent::keyDown('D'))
            dest.x++;

        window->drawTexture(blueSquare, dest);
        window->drawRect(src, 0, 255, 0);

        


        window->updateBuffer();
    }
    soundEffect.freeSFX();
    bSound::freeMUS();
    bSound::closeAudio();
    window->closeWindow();
    return 0;
}


