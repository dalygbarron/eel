#ifndef TILE_CHUNK_H
#define TILE_CHUNK_H

#include "static/xml/pugixml.hpp"

/**
 * Represents a chunk of tiles within a tile map.
 */
class TileChunk {
    public:
        /**
         * Creates the tile chunk.
         * @param node is the xml node to read the chunk out of.
         */
        TileChunk(pugi::xml_node node);

        /**
         * Deletes the tiles.
         */
        ~TileChunk();

        /**
         * Sets a tile in the chunk.
         * @param pos   is the location of the tile to set.
         * @param value is the value to set the tile to.
         */
        void setTile(sf::Vector3i pos, unsigned char value);

        /**
         * Gives you the tiles in the chunk with read only access.
         * @return all of the tiles by rows and then columns and then layers.
         */
        unsigned char const *getTiles() const;

        /**
         * Gives you the size of the chunk.
         * @return the size on the x and y axis.
         */
        sf::Vector2i getSize() const;

        /**
         * Gives you the offset of the chunk in the world.
         * @return the offset.
         */
        sf::Vector2i getOffset() const;

    private:
        unsigned char *tiles;
        sf::Vector2i size;
        sf::Vector2i offset;
};

#endif
