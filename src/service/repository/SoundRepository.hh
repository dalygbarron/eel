#ifndef SOUND_REPOSITORY_H
#define SOUND_REPOSITORY_H

#include "service/repository/Repository.hh"
#include <SFML/Audio.hpp>

/**
 * Repository for sounds.
 */
class SoundRepository: public Repository<sf::SoundBuffer *> {
    private:
        virtual sf::SoundBuffer *create(char const *name) override;
};

#endif
