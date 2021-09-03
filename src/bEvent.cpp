
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
            
            case SDL_KEYDOWN:

                break;

            case SDL_KEYUP:
                
                break;
            
            case SDL_WINDOWEVENT:

                break;

            default:
                printf("Look: %u\n", event.type);
                break;
        }
    }
    return true;
}
