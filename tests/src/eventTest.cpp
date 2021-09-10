
// Bee Bussell
// Sept 2, 2021
// A Window that will close because I have implemented events :3

#include <iostream>
#include <stdint.h>

#include <BML/BML.h>



int main() {

    const char *title = "silly";
    uint16_t zero = 0;
    uint16_t width = 320;
    uint16_t height = 240;


    bool run = true;

    BML_Init();
    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->createWindow();

    while(run) {

        window->clearBuffer();

        // Do Drawings
        run = bEvent::eventLoop();

        if (bEvent::keyDown((uint8_t)21))
            printf("Hey you pressed q\n");

        window->updateBuffer();
    }
    
    window->closeWindow();
    BML_Close();
    return 0;
}


