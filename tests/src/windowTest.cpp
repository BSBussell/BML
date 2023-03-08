
// Bee Bussell
// Sept 2, 2021
// A Window that will never close because I haven't implemented event's yet :3

#include <iostream>
#include <string>
#include <stdint.h>
#include <BML/BML.h>

int main() {

    const char *title = "silly";
    uint16_t zero = 0;
    uint16_t width = 320;
    uint16_t height = 240;

    BML_Init();
    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    bRenderer *r = window->createWindow();

    while(1) {

        r->clearBuffer();

        // Do Drawings

        r->updateBuffer();
    }

    BML_Close();
    return 0;
}


