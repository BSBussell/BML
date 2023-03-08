
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
    bRenderer *r = window->createWindow();

    bRect dest = {10,10,320,240};
    bRect src = {10,10,320,240};
   

    //bTexture blueSquare = window->initTexture("/home/bee/Development/BML/tests/resources/blueSquare.png", src);
    bTexture blueSquare = r->initTexture("../resources/blueSquare.png", src);
    
    while(run) {

       r->clearBuffer();

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

       r->drawTexture(blueSquare, dest);
       r->drawRect(src, 0, 255, 0);

        


       r->updateBuffer();
    }
    
    window->closeWindow();
    BML_Close();
    return 0;
}


