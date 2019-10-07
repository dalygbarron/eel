#ifndef TILESET_REPOSITORY_H
#define TILESET_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "service/repository/TextRepository.hh"
#include "service/repository/TextureRepository.hh"
#include "model/Tileset.hh"

/**
 * Repository for tileset objects.
 */
class TilesetRepository: public Repository<Tileset *> {
    public:
        /**
         * Builds the repo and injects the dependencies.
         * @param textRepo    gives access to text files.
         * @param textureRepo gives access to textures.
         */
        TilesetRepository(
            TextRepository *textRepo,
            TextureRepository *textureRepo
        );

    private:
        TextRepository *textRepo;
        TextureRepository *textureRepo;

        virtual Tileset *create(char const *name) override;
};

#endif
