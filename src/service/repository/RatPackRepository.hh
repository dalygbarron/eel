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
         */
        RatPackRepository(
            char const *root,
            TextRepository const *TextRepo,
            Repository<sf::Texture> const *textureRepo
        );

    private:
        TextRepository const *textRepo;
        Repository<sf::Texture> const *textureRepo;

        virtual RatPack *create(
            char const *name,
            char const *key
        ) const override;
};

#endif
