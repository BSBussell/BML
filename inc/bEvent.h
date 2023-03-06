
// Bee Bussell
// Sept 2, 2021
// Event Handler

#ifndef BML_EVENT_H
#define BML_EVENT_H

#include "BML.h"

// TODO: Allow custom actions. ex: a user can tie action jump to keydown spacebar
//       See godot implementation

class bEvent {

public:

    const static uint8_t b_KEYDOWN = 0b0001;
    const static uint8_t b_KEYSTILLDOWN = 0b0010;
    const static uint8_t b_KEYUP = 0b0100;
    const static uint8_t b_KEYSTILLUP = 0b1000;

    static bool eventLoop();

    static bool keyDown(uint8_t key );
    static bool keyDown(const char key);
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

    inline static uint8_t b_KEYSTATE[82];

};



#endif
