#ifndef TEXTURE_REPOSITORY_H
#define TEXTURE_REPOSITORY_H

#include "service/repository/Repository.hh"
#include <SFML/Graphics.hpp>

/**
 * Repository for textures.
 */
class TextureRepository: public Repository<sf::Texture *> {
    private:
        virtual sf::Texture *create(char const *name) override;
};

#endif
