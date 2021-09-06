
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented events :3

#include <iostream>
#include <stdint.h>

#include "bSDL.h"
#include <filesystem>
namespace fs = std::filesystem;


int main(int argc, char **argv) {

    const char *title = "silly";
    uint16_t zero = 0;
    uint16_t width = 320;
    uint16_t height = 240;


    bool run = true;

    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->createWindow();

    bRect dest = {10,10,320,240};
    bRect src = {10,10,320,240};
   
    std::cout << fs::path(argv[0]).parent_path() << std::endl;    

    while(run) {

        window->clearBuffer();

        // Event loop
        run = bEvent::eventLoop();

        window->addTexture("~/Development/bSDL/tests/resources/blueSquare.png", src, dest);
        window->addRect(src, 0, 255, 0);

        if (bEvent::keyDown(21))
            printf("Hey you pressed q\n");

        window->updateBuffer();
    }
    
    window->closeWindow();
    return 0;
}


