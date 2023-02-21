
// Bee Bussell
// Sept 7, 2021
// Sound Class

#include "bSound.h"

// Opens audio
// Inits mix
bool bSound::openAudio() {

    if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        printf("---  SDL_Mixer failed to initialize     ---\n");
        printf("%s", Mix_GetError());
        return false;
    }

    Mix_Init(MIX_INIT_MOD);
    Mix_Volume(-1, MIX_MAX_VOLUME);
    printf("---  SDL_Mixer Successfully Initalized     --- \n");
    return true;
}

// Closes audio
// Quits mix
void bSound::closeAudio() {

    Mix_CloseAudio();
    Mix_Quit();
}

// Loads Music
bool bSound::loadMUS(const char* src) {

    /*std::string relativePath = std::string(SDL_GetBasePath());
    relativePath += std::string(src);*/

    song = Mix_LoadMUS(BML_GetPath(src).c_str());
    if (song == NULL) {
        printf("--- Music File Failed to Load ---\n");
        printf("%s", Mix_GetError());
        return false;
    }
    return true;
}

bool bSound::playMUS(uint8_t loops) {

    if (Mix_PlayMusic(song, loops) == -1) {
        printf("---   Music Failed to Play  ---\n");
        printf("%s", Mix_GetError());
        return false;
    }      
    return true;
}

void bSound::setMUSVOL(double perc) {
    
    Mix_VolumeMusic(MIX_MAX_VOLUME*perc);
}

// Free Music
void bSound::freeMUS() {

    Mix_FreeMusic(song);
}

bool bSound::loadSFX(const char* src) {

    /*std::string relativePath = std::string(SDL_GetBasePath());
    relativePath += std::string(src);*/

    wave = Mix_LoadWAV(BML_GetPath(src).c_str());
    if (wave == NULL) {
        printf("%s", Mix_GetError());
        printf("--- Audio File Failed to Load ---\n");
        return false;
    }
    return true;
}

bool bSound::playSFX(uint8_t channel, uint8_t loops) {

    Mix_VolumeChunk(wave, MIX_MAX_VOLUME);

    if (Mix_PlayChannel(channel, wave, loops) == -1) {
        printf("%s", Mix_GetError());
        printf("--- Audio File Failed to Play ---\n");
        return false;
    }
    return true;

}

void bSound::setSFXVOL(double perc) {

    Mix_VolumeChunk(wave, (MIX_MAX_VOLUME*perc));
}

void bSound::freeSFX() {

    Mix_FreeChunk(wave);
}

void bSound::setGBLVOL(double perc) {

    Mix_Volume(-1, (MIX_MAX_VOLUME*perc));
}

bSound::bSound() {

}

bSound::~bSound() {

}
