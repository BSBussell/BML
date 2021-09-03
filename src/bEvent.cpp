
// Bee Bussell
// <DATE>
// bEvent Handler

#include "bEvent.h"

bool bEvent::keyDown(uint8_t key) {


    if (key%2 == 0)
        return ((b_KEYSTATE[key/2] >> 4) == b_KEYDOWN);
    else
        return ((b_KEYSTATE[key/2] & 0b00001111) == b_KEYDOWN);

}

bool bEvent::keyUp(uint8_t key) {

    if (key%2 == 0)
        return ((b_KEYSTATE[key/2] >> 4) == b_KEYUP);
    else
        return (((b_KEYSTATE[key/2] << 4) >> 8) == b_KEYUP);
    
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
                    b_KEYSTATE[event.key.keysym.scancode/2] ^= b_KEYDOWN << (4-(4-(event.key.keysym.scancode%2)));
               //printf("Key Down: %u\n", event.key.keysym.scancode);
                break;

            case SDL_KEYUP:

                if (event.key.keysym.scancode <= 82)
                    b_KEYSTATE[event.key.keysym.scancode/2] ^= b_KEYUP << (4-(4-(event.key.keysym.scancode%2)));
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
