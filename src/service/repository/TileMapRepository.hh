#ifndef TILE_MAP_REPOSITORY_H
#define TILE_MAP_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "model/TileMap.hh"

/**
 * Repository for Tile Maps.
 */
class TileMapRepository: public Repository<TileMap *> {
    public:
        /**
         * Creates the tilemap repo and gives it a pointer to a tileset repo
         * which is needed to create tile maps.
         * @param tilesetRepo is the dependency of the tilemap repo.
         */
        TileMapRepository(TilesetRepository *tilesetRepo);

    private:
        TilesetRepository *tilesetRepo;

        virtual TileMap *create(char const *filename) override;
};

#endif
