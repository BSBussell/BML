
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented events :3

#include <iostream>
#include <stdint.h>

#include <BML/BML.h>



int main() {

    const char *title = "silly";
    Uint16 zero = 0;
    Uint16 width = 320;
    Uint16 height = 240;


    bool run = true;

    BML_Init();
    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    bRenderer *r = window->createWindow();

    while(run) {

        r->clearBuffer();

        // Do Drawings
        run = bEvent::eventLoop();

        if (bEvent::keyDown((Uint8)21))
            printf("Hey you pressed q\n");

        r->updateBuffer();
    }
    
    window->closeWindow();
    BML_Close();
    return 0;
}


