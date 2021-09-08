
// Bee Bussell
// Sept 7, 2021
// Sound Header

#ifndef bSound_h
#define bSound_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdint.h>
#include <string>

class bSound {

public:

    bSound();
    ~bSound();

    // Only one file considered "music" can play at a time
    static bool loadMUS(const char* src);
    static bool playMUS(uint8_t loops);
    static void setMUSVOL(double perc);
    static void freeMUS();

    bool loadSFX(const char* src);
    bool playSFX(uint8_t channel, uint8_t loops);
    void setSFXVOL(double perc);
    void freeSFX();

    static void setGBLVOL(double perc);

    static bool openAudio();
    static void closeAudio();


private:

    inline static Mix_Music *song;
    Mix_Chunk *wave = NULL;    
};

#endif
