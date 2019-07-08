#ifndef RADIO_H
#define RADIO_H

#include "Repository.hh"
#include "Listener.hh"
#include "Constant.hh"
#include <SFML/Audio.hpp>

/**
 * Handles the playing of sounds and music.
 */
class Radio {
    Repository *repository;
    sf::Music *currentSong;
    sf::Sound sounds[Constant::SOUND_LIMIT];
    class {
    public:
        sf::Sound sound;
        Listener *listener;
    } soundListeners[Constant::SOUND_LISTENER_LIMIT];

public:
    /**
     * Builds the radio.
     * @param repository is the source of sound files.
     */
    Radio(Repository *repository);

    /**
     * Starts a nice song playing, unless it is already playing in which case it does nothing.
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
     */
    void playSound(char const *sound);

    /**
     * Plays a sound in 3d space.
     * Note that there is a maximum allowed number of sounds at once.
     * @see Constant::SOUND_LIMIT.
     * @param sound is the name of the sound file.
     * @param pos   is the 3d location to play the sound at relative to the player.
     */
    void playSoundAt(char const *sound, sf::Vector3f pos);

    /**
     * Starts a sound playing, and connects a listener to know when it is done.
     * Note that there is a maximum allowed number of sound listeners at once.
     * @see Constant::SOUND_LISTENER_LIMIT.
     * @param sound    is the name of the sound to play.
     * @param listener is the listener to inform when the song ends. If the listener is null, nobody is informed.
     */
    void playSoundListened(char const *sound, Listener *listener);

    /**
     * Starts a sound playing as from a position, and connects a listener to know when it is done.
     * Note that there is a maximum allowed number of sound listeners at once.
     * @see Constant::SOUND_LISTENER_LIMIT.
     * @param sound    is the name of the sound to play.
     * @param pos      is the 3d place the song sounds like it's coming from relative to the player.
     * @param listener is the listener to inform when the song ends. If the listener is null, nobody is informed.
     */
    void playSoundAtListened(char const *sound, sf::Vector3f pos, Listener *listener);
};

#endif
