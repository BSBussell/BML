
// Bee Bussell
// Sept 2, 2021
// Event Handler

#ifndef bEvent_h
#define bEvent_h

#include <SDL2/SDL.h>
#include <stdint.h>

class bEvent {

public:
    static bool eventLoop();

    static bool KeyDown(const char *key );
    static bool KeyStillDown(const char *key );
    static bool KeyUp(const char *key );
    static bool KeyStillUp(const char *key );
    /* 
    static bool MouseDown(const char *key );
    static bool MouseStillDown(const char *key );
    static bool MouseUp(const char *key );
    static bool MouseStillUp(const char *key );
    */
    
private:
    
    bEvent();
    

};



#endif
