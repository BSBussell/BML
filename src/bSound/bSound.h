
// Bee Bussell
// Sept 7, 2021
// Sound Header

#ifndef bSound_h
#define bSound_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdint.h>


class bSound {

public:

    bSound();
    ~bSound();

    playSFX(uint8_t channel, );
    playMusic();

    static bool openAudio();
    static bool closeAudio();


private:

    Mix_Music *song = NULL;
    Mix_Chunk *wave = NULL;    
};

#endif
