#ifndef RADIO_H
#define RADIO_H

#include "static/Constant.hh"
#include "service/Repository.hh"
#include <SFML/Audio.hpp>

/**
 * Handles the playing of sounds and music.
 */
class Radio {
    public:
        constexpr static int const SOUND_LIMIT = 16;

        /**
         * Builds the radio.
         * @param soundRepo is name of the sound repo.
         * @param musicRepo is the name of the music repo.
         */
        Radio(SoundRepository *soundRepo, MusicRepository *musicRepo);

        /**
         * Starts a nice song playing, unless it is already playing in which case
         * it does nothing.
         * @param song is the name of the song to play.
         */
        void playSong(char const *song);

        /**
         * Stops the music that is playing.
         */
        void stopSong();

        /**
         * Plays a sound.
         * Note that there is a maximum allowed number of sounds at once.
         * @see Constant::SOUND_LIMIT.
         * @param sound is the name of the sound file.
         * @return length of the sound in seconds.
         */
        float playSound(char const *sound);
    
    private:
        SoundRepository *soundRepo;
        MusicRepository *musicRepo;
        sf::Music *currentSong;
        sf::Sound sounds[Radio::SOUND_LIMIT];
};

#endif
