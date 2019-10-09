#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "model/Tileset.hh"
#include "model/Chunk.hh"
#include "service/repository/TilesetRepository.hh"
#include "static/Utils.hh"
#include "static/xml/pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

// Forward Declaration.
class TileMapRepository;

/**
 * Represents a game map.
 */
class TileMap {
    friend class TileMapRepository;
    public:
        /**
         * Creates a tilemap by putting in all it's data.
         * @param tileSize is the size of each tile in the actual map like how
         *                 they fit together kinda thing.
         * @param tileset  is the tileset that the tiles in the map belong to.
         */
        TileMap(sf::Vector2u tileSize, Asset<Tileset *> const *tileset);

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

    private:
        sf::Vector2u tileSize;
        Asset<Tileset *> const *tileset;
        std::unordered_map<sf::Vector2i, Chunk *, Utils::VectHash> chunks;

        /**
         * Adds a chunk into the map's hashmap of chunks.
         * @param offset is the 2d location of the chunk in increments of chunk
         *               size which should be the same for all chunks.
         * @param chunk  is the chunk to add.
         */
        void addChunk(sf::Vector2i offset, Chunk *chunk);
};

#endif
