#ifndef RAT_PACK_REPOSITORY_H
#define RAT_PACK_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "model/RatPack.hh"

/**
 * Repository for rat pack sprite sheets.
 */
class RatPackRepository: public Repository<RatPack> {
    public:
        /**
         * Builds the repo.
         * @param root is the base directory from which they will be loaded.
         * @param textRepo is the text repository for reading the xml.
         * @param textureRepo is the texture repo, to which this repo requires
         *                    non const access. I know that is heavy but it is
         *                    because rat packs need to have editable textures.
         */
        RatPackRepository(
            char const *root,
            TextRepository const *textRepo,
            Repository<sf::Texture> *textureRepo
        );

    private:
        TextRepository const *textRepo;
        Repository<sf::Texture> *textureRepo;

        virtual RatPack *create(
            char const *name,
            char const *key
        ) const override;
};

#endif
