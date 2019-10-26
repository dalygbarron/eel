#ifndef TILE_MAP_REPOSITORY_H
#define TILE_MAP_REPOSITORY_H

#include "service/repository/Repository.hh"
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
            Repository<char> *textRepo,
            Repository<Tileset> *tilesetRepo
        );

    private:
        Repository<char> *textRepo;
        Repository<Tileset> *tilesetRepo;

        virtual TileMap *create(
            char const *filename,
            char const *key
        ) const override;
};

#endif
