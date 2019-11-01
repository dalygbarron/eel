#ifndef TEXTURE_REPOSITORY_H
#define TEXTURE_REPOSITORY_H

#include "service/repository/Repository.hh"
#include <SFML/Graphics.hpp>

/**
 * Repository for textures.
 */
class TextureRepository: public Repository<sf::Texture> {
    public:
        /**
         * Creates the repo.
         * @param root is the root directory assets are loaded from.
         */
        TextureRepository(char const &root);

    private:
        virtual sf::Texture &create(
            char const &name,
            char const &key
        ) const override;
};

#endif
