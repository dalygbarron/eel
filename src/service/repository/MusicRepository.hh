#ifndef MUSIC_REPOSITORY_H
#define MUSIC_REPOSITORY_H

#include "service/repository/Repository.hh"
#include <SFML/Audio.hpp>

/**
 * Repository for musics.
 */
class MusicRepository: public Repository<sf::Music *> {
    public:
        /**
         * Creates the music repo.
         * @param root is the root directory from which it loads the shit.
         */
        MusicRepository(char const *root);

    private:
        virtual sf::Music *create(char const *filename) override;
};

#endif
