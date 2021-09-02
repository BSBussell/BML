
// Bee Bussell
// <DATE>
// <DESCRIPTION>

#include <iostream>
#include <string>
#include <stdint.h>
#include "bWindow.h"

int main() {

    const char *title = "silly";
    uint16_t zero = 0;
    uint16_t width = 320;
    uint16_t height = 240;

    bWindow* window = new bWindow(title, zero, zero, width, height);
    window->toggleResizeable();
    window->toggleHardwareRender();
    window->createWindow();

    while(1) {

        window->clearBuffer();

        // Do Drawings

        window->updateBuffer();
    }

    return 0;
}


