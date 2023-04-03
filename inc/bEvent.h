
// Bee Bussell
// Sept 2, 2021
// Event Handler

#ifndef BML_EVENT_H
#define BML_EVENT_H

#include <array>
#include <algorithm>

#include "BML.h"

// TODO: Allow custom actions. ex: a user can tie action jump to keydown spacebar
//       See godot implementation

class bEvent {

public:

    const static Uint8 b_KEYDOWN = 0b0001;
    const static Uint8 b_KEYSTILLDOWN = 0b0010;
    const static Uint8 b_KEYUP = 0b0100;
    const static Uint8 b_KEYSTILLUP = 0b1000;

    static bool eventLoop();

    static bool keyDown(Uint8 key );
    static bool keyDown(const char key);

	static bool keyJustDown(Uint8 key, Uint8 frames = 1);
	static bool keyJustDown(const char key, Uint8 frames = 1);

	static bool keyStillDown(const char *key );

	static bool keyUp(Uint8 key );
    static bool keyStillUp(const char *key );
    
    /*

    static bool MouseDown(const char *key );
    static bool MouseStillDown(const char *key );
    static bool MouseUp(const char *key );
    static bool MouseStillUp(const char *key );

    */

private:

    bEvent();

	inline static std::array<Uint8, 83> b_KEYSTATE = {};
	inline static std::array<std::array<Uint8, 83>, 100> b_KEYBUFFER = {};

	inline static Uint8 b_FRAME_COUNT = 0;

};



#endif
