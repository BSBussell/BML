
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented events :3

#include <iostream>
#include <stdint.h>
#include <BML/BML.h>


int main() {

    bool run = true;

    BML_Init();
    bWindow* window = new bWindow("silly", 0, 0, 1600, 900);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->toggleVSync();
    window->toggleHighDPI();
    bRenderer *r = window->createWindow();

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

    //bTexture blueSquare = window->initTexture("/home/bee/Development/BML/tests/resources/blueSquare.png", src);
    bTexture blueSquare = r->initTexture("../resources/blueSquare.png", src);
    
    double vol = .5;

    while(run) {

        r->clearBuffer();

        // Event loop
        run = bEvent::eventLoop();

        if (bEvent::keyDown('W')) {
            dest.y--;
            vol += .1;
            bSound::setMUSVOL(vol);
        } 
        if (bEvent::keyDown('S')) {
            dest.y++;
            vol -= .1;
            bSound::setMUSVOL(vol);
        }
        if (bEvent::keyDown('A')) {
            dest.x--;
        }
        if (bEvent::keyDown('D')) {
            dest.x++;
        }
        r->drawTexture(blueSquare, dest);
        r->drawRect(src, 0, 255, 0);

        


        r->updateBuffer();
    }
    soundEffect.freeSFX();
    bSound::freeMUS();
    bSound::closeAudio();
    window->closeWindow();
    BML_Close();
    return 0;
}


