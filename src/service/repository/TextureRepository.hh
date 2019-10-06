#ifndef TEXTURE_REPOSITORY_H
#define TEXTURE_REPOSITORY_H

#include "service/repository/Repository.hh"

/**
 * Repository for textures.
 */
class TextureRepository: public Repository<sf::Texture *> {
    public:
        /**
         * Creates the texture repository.
         * @param config lets it find the root directory and stuff.
         */
        TextureRepository(Config const *config);

    private:
        Config const *config;

        virtual sf::Texture *create(char const *name) override;
};

#endif
