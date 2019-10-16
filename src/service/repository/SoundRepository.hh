#ifndef SOUND_REPOSITORY_H
#define SOUND_REPOSITORY_H

#include "service/repository/Repository.hh"
#include <SFML/Audio.hpp>

/**
 * Repository for sounds.
 */
class SoundRepository: public Repository<sf::SoundBuffer> {
    public:
        /**
         * Creates the repo.
         * @param root is the root dir to load files from.
         */
        SoundRepository(char const *root);

    private:
        virtual sf::SoundBuffer *create(
            char const *filename,
            char const *key
        ) const override;
};

#endif
