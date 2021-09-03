
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented event(singular) :3

#include <iostream>
#include <stdint.h>

#include "bWindow.h"
#include "bEvent.h"



int main() {

    const char *title = "silly";
    uint16_t zero = 0;
    uint16_t width = 320;
    uint16_t height = 240;


    bool run = true;

    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->createWindow();

    while(run) {

        window->clearBuffer();

        // Do Drawings
        run = bEvent::eventLoop();

        window->updateBuffer();
    }
    
    window->closeWindow();
    return 0;
}

