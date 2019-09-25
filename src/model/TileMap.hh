#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "model/Tileset.hh"
#include <SFML/Graphics.hpp>

// Forward Declaration.
class Repository;

/**
 * Represents a game map as it is loaded from the tiled editor.
 */
class TileMap {
    public:
        /**
         * Represents the ways in which the map can be oriented.
         */
        enum Orientation {
            ORTHAGONAL,
            ISOMETRIC
        };

        /**
         * Creates a tilemap out of an input stream.
         * @param data is the contents of the tiled editor xml file the map is
         *             being loaded from.
         */
        TileMap(char const *data, Repository *repository);

        /**
         * Deletes the tile map's set of tiles. Note that this is only deleting
         * the configuration of tiles in this map, not the tile or tileset
         * objects.
         */
        ~TileMap();

        /**
         * Gives you all of the tiles in the map in a read only form.
         * @return a pointer to the first tile in the whole map.
         */
        unsigned char const *getTiles() const;

        /**
         * Gives you the dimensions of the map.
         * @return the width, the height, and the number of layers.
         */
        sf::Vector3i getSize() const;

        /**
         * Gives the dimensions that the map gives to tiles.
         * @return the width and height of tiles.
         */
        sf::Vector2u getTileSize() const;

        /**
         * If this map is a map that fits with other maps around the joint then
         * this is the distance in two dimensions that this map is from the
         * original map.
         * @return the distance in each direction.
         */
        sf::Vector2i getOffset() const;

        /**
         * Takes a string containing the name of an orientation and parses it
         * into an orientation enum. If it is not recognised it logs a warning
         * and defaults to isometric.
         * @param orientation is the string to read.
         * @return the orientation enum value.
         */
        static TileMap::Orientation parseOrientation(char const *orientation);

    private:
        Tileset const *tileset;
        sf::Vector3i size;
        sf::Vector2u tileSize;
        sf::Vector2i offset;
        unsigned char *tiles;
        sf::IntRect *regions;
        TileMap::Orientation orientation;
};

#endif
