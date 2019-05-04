#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * Manages sounds and music.
 */
namespace Audio {
    /**
     * Initialises the audio system.
     */
    void init();

    /**
     * Turns off the audio system.
     */
    void close();

    /**
     * Play a track.
     * @param filename is the name of the track to play. NB: must be 128 characters or less including null terminator.
     * @param restart  tells if this track is already playing whether we should start it again.
     */
    void play(char const *filename, int restart = false);

    /**
     * Stops the currently playing music.
     */
    void stop();
}

#endif
