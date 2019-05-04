#include "Audio.hh"

#include <iostream>
#include <string.h>

#define NAME_BUFFER_SIZE 128

char nameBuffer[NAME_BUFFER_SIZE];
Mix_Music *music = 0;

void Audio::init() {
    int mixerFlags = MIX_INIT_OGG;
    if (!(Mix_Init(mixerFlags) & mixerFlags)) {
        std::cerr << "Couldn't open sdl mixer: " << Mix_GetError() << std::endl;
        throw -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        std::cerr << "Could not open desired audio format: " << Mix_GetError() << std::endl;
        throw -1;
    }
}

void Audio::close() {
    if (music) Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
}

void Audio::play(char const *filename, int restart) {
    if (!restart && music && strcmp(nameBuffer, filename) == 0) return;
    if (music) Mix_FreeMusic(music);
    strcpy(nameBuffer, filename);
    music = Mix_LoadMUS(filename);
    if (!music) {
        std::cerr << "Couldn't load music file " << filename << std::endl;
        throw -1;
    }
    Mix_PlayMusic(music, -1);
}

void Audio::stop() {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = 0;
}
