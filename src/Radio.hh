#ifndef RADIO_H
#define RADIO_H

#include "Repository.hh"

/**
 * Handles the playing of sounds and music.
 */
class Radio {
    Repository *repository;
    char currentSong[Constant::FILENAME_BUFFER_SIZE];

public:
    /**
     * Builds the radio.
     * @param repository is the source of sound files.
     */
    Radio(Repository *repository);

    void playSong()

};

#endif
