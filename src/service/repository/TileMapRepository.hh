#ifndef TILE_MAP_REPOSITORY_H
#define TILE_MAP_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "service/repository/TilesetRepository.hh"
#include "service/repository/TextRepository.hh"
#include "model/TileMap.hh"

/**
 * Repository for Tile Maps.
 */
class TileMapRepository: public Repository<TileMap> {
    public:
        /**
         * Creates the tilemap repo and gives it a pointer to a tileset repo
         * which is needed to create tile maps.
         * @param root           is the root directory to load from.
         * @param textRepository is the text repo used to open it's own xml.
         * @param tilesetRepo    is the dependency of the tilemap repo.
         */
        TileMapRepository(
            char const *root,
            TextRepository *textRepo,
            TilesetRepository *tilesetRepo
        );

    private:
        TextRepository *textRepo;
        TilesetRepository *tilesetRepo;

        virtual TileMap *create(
            char const *filename,
            char const *key
        ) override;
};

#endif
