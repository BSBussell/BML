
// Bee Bussell
// Sept 2, 2021
// bEvent Handler

#include "bEvent.h"

bool bEvent::keyDown(uint8_t key) {


    return (b_KEYSTATE[key] == b_KEYDOWN);
}

bool bEvent::keyDown(const char key) {

    if (toupper(key) >= 'A' && toupper(key) <= 'Z')
        return (b_KEYSTATE[toupper(key)-61] == b_KEYDOWN);
    fprintf(stderr, "Warning, invalid key check");
    return false;
}

bool bEvent::keyUp(uint8_t key) {

    return (b_KEYSTATE[key]== b_KEYUP);
}

bool bEvent::eventLoop() {
    
    SDL_Event event;
    
    while( SDL_PollEvent( &event ) ) {

        switch(event.type) {
            
            case SDL_QUIT:
                return false;
            
            case SDL_KEYDOWN:
                // THIS IS FUCKY
                if (event.key.keysym.scancode <= 82)
                    b_KEYSTATE[event.key.keysym.scancode] = b_KEYDOWN;
               //printf("Key Down: %u\n", event.key.keysym.scancode);
                break;

            case SDL_KEYUP:

                if (event.key.keysym.scancode <= 82)
                    b_KEYSTATE[event.key.keysym.scancode] = b_KEYUP;
                break;

            case SDL_WINDOWEVENT:
                break;

            default:
                //printf("Look: %u\n", event.type);
                break;
        }
    }
    return true;
}
