
// Bee Bussell
// Sept 2, 2021
// bEvent Handler

#include "bEvent.h"

bool bEvent::keyDown(Uint8 key) {


    return (b_KEYSTATE[key] == b_KEYDOWN);
}

bool bEvent::keyDown(const char key) {

    if (toupper(key) >= 'A' && toupper(key) <= 'Z')
        return (b_KEYSTATE[toupper(key)-61] == b_KEYDOWN);
    fprintf(stderr, "Warning, invalid key check");
    return false;
}

bool bEvent::keyUp(Uint8 key) {

    return (b_KEYSTATE[key]== b_KEYUP);
}

bool bEvent::keyJustDown(Uint8 key, Uint8 frames) {

	// Check if the key was not pressed in the frame immediately before the last 'frames' frames
    int prevBufferIndex = (b_FRAME_COUNT - frames + 99) % 100;

	if (b_KEYBUFFER[prevBufferIndex][key] == b_KEYDOWN) {
        return false;
    }

	// Check if the key was pressed within the last 'frames' frames
    for (int i = 0; i < frames; i++) {
        int bufferIndex = (b_FRAME_COUNT - i + 100) % 100; // Calculate the buffer index for the frame
        if (b_KEYBUFFER[bufferIndex][key] == b_KEYDOWN) {
            return true;
        }
    }

    return false;
}

bool bEvent::keyJustDown(const char key, Uint8 frames) {

	SDL_Keycode keycode;

    // Check if the input character is a valid letter key
    if (toupper(key) >= 'A' && toupper(key) <= 'Z') {
        keycode = SDL_Keycode(toupper(key));
    }
    // Check if the input character is a valid number key
    else if (key >= '0' && key <= '9') {
        keycode = SDL_Keycode(key);
    }
    // Check if the input character is a spacebar
    else if (key == ' ') {
        keycode = SDLK_SPACE;
    }
    // If the input character is invalid, print a warning and return false
    else {
        fprintf(stderr, "Warning, invalid key check");
        return false;
    }

    // Convert the character to the associated SDL scancode
    Uint8 scancode = SDL_GetScancodeFromKey(keycode);

    // Call the keyJustDown function with the SDL scancode
    return keyJustDown(scancode, frames);
}

// I do not feel good about this :3
bool bEvent::eventLoop() {
    
    SDL_Event event;


    while( SDL_PollEvent( &event ) ) {

        switch(event.type) {
            
            case SDL_QUIT:

                return false;
            
            case SDL_KEYDOWN:
                // THIS IS FUCKY
                if (event.key.keysym.scancode <= 82) {

					b_KEYSTATE[event.key.keysym.scancode] = b_KEYDOWN;

				}
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

	b_FRAME_COUNT = (b_FRAME_COUNT + 1) % 100;

	// Assign array at b_Frame_Count to be b_KEYSTATE
	b_KEYBUFFER[b_FRAME_COUNT] = b_KEYSTATE;

    return true;
}
