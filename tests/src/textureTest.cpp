
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented events :3

#include <iostream>
#include <stdint.h>

#include "bSDL.h"
#include <filesystem>
namespace fs = std::filesystem;


int main() {

    const char *title = "silly";
    uint16_t zero = 0;
    uint16_t width = 640;
    uint16_t height = 480;


    bool run = true;

    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->createWindow();

    bRect dest = {10,10,320,240};
    bRect src = {10,10,320,240};
   

    //bTexture blueSquare = window->initTexture("/home/bee/Development/bSDL/tests/resources/blueSquare.png", src);
    bTexture blueSquare = window->initTexture("../resources/blueSquare.png", src);
    
    while(run) {

        window->clearBuffer();

        // Event loop
        run = bEvent::eventLoop();

        if (bEvent::keyDown(26)) {
            dest.y--;
        }
        if (bEvent::keyDown(22)) {
            dest.y++;
        }

        window->drawTexture(blueSquare, dest);
        window->drawRect(src, 0, 255, 0);

        


        window->updateBuffer();
    }
    
    window->closeWindow();
    return 0;
}


