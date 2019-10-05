#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "model/Tileset.hh"
#include "static/Utils.hh"
#include "static/xml/pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

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
         * @param node       is the xml node to read the map from.
         * @param repository is the repo which is used to load in child bits
         *                   like the tileset.
         * @param dir        the directory the file existed in.
         */
        TileMap(pugi::xml_node node, Repository *repository, char const *dir);

        /**
         * Deletes the map's chunks.
         */
        ~TileMap();

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
         * Takes a string containing the name of an orientation and parses it
         * into an orientation enum. If it is not recognised it logs a warning
         * and defaults to isometric.
         * @param orientation is the string to read.
         * @return the orientation enum value.
         */
        static TileMap::Orientation parseOrientation(char const *orientation);

    private:
        Tileset const *tileset;
        sf::Vector2u tileSize;
        std::unordered_map<
            sf::Vector2i,
            unsigned char *,
            Utils::VectHash
        > chunks;
        sf::IntRect *regions;
        TileMap::Orientation orientation;
};

#endif
