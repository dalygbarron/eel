#ifndef TILED_POPULABLE_H
#define TILED_POPULABLE_H

#include "service/repository/Repository.hh"
#include "model/Tileset.hh"

/**
 * Defines a type of object that can build it's data by parsing a tiled editor
 * tile map.
 */
class TiledPopulable {
    public:
        /**
         * Populate the class with the data from a given tiled map which has
         * been loaded in as a string.
         * @param tilesetRepo is used for loading the map's tileset.
         * @param key         is the key of the tiled map file.
         * @param data        is the xml data as a string.
         */
        void tiledPopulate(
            Repository<Tileset> const &tilesetRepo,
            char const &key,
            char const &data
        );

    private:
        /**
         * Passes the basic properties of the currently loaded tile map.
         * @param size     is the 2d size of the map.
         * @param tileSize is the 2d size of tiles in the map.
         * @param bg       is the background colour of the map.
         */
        virtual void tiledMap(
            sf::Vector2u size,
            sf::Vector2u tileSize,
            sf::Color bg
        ) = 0;

        /**
         * Passes the tileset used in a given tile map.
         * @param tileset is the tileset in the currently loaded tile map.
         */
        virtual void tiledTileset(Asset<Tileset> const &tileset) = 0;

        virtual void tiledLayer() = 0;

        virtual void tiledChunk() = 0;
};

#endif
