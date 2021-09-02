
// Bee Bussell
// <DATE>
// <DESCRIPTION>

#include "bEvent.h"

bool bEvent::eventLoop() {
    
    SDL_Event event;
    
    while( SDL_PollEvent( &event ) ) {

        switch(event.type) {
            case SDL_QUIT:
                return false;
            default:
                break;
        }
    }
    return true;
}
