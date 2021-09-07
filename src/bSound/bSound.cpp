
// Bee Bussell
// Sept 7, 2021
// Sound Class

#include "bSound.h"

bool openAudio() {

    if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        printf("...    SDL_Mixer failed to initialize  ...\n");
        return false;
    }
    printf("...    SDL_ Mixer Initalized  ... \n");
    return true;
}

bool closeAudio() {

    Mix_CloseAudio();
}

bSound::bSound() {

}

bSound::~bSound() {

}
