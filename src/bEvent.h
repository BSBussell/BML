
// Bee Bussell
// Sept 2, 2021
// Event Handler

#ifndef bEvent_h
#define bEvent_h

#include <SDL2/SDL.h>
#include <stdint.h>

class bEvent {

public:

    const static uint8_t b_KEYDOWN = 0b0001;
    const static uint8_t b_KEYSTILLDOWN = 0b0010;
    const static uint8_t b_KEYUP = 0b0100;
    const static uint8_t b_KEYSTILLUP = 0b1000;

    static bool eventLoop();

    static bool keyDown(uint8_t key );
    static bool keyStillDown(const char *key );
    static bool keyUp(uint8_t key );
    static bool keyStillUp(const char *key );
    /*

    static bool MouseDown(const char *key );
    static bool MouseStillDown(const char *key );
    static bool MouseUp(const char *key );
    static bool MouseStillUp(const char *key );

    */

private:

    bEvent();

    inline static uint8_t b_KEYSTATE[41];

};



#endif
