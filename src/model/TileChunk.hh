#ifndef TILE_CHUNK_H
#define TILE_CHUNK_H

/**
 * Represents a chunk of tiles within a tile map.
 */
class TileChunk {
    public:
        sf::Vector3i const size;
        sf::Vector2i const offset;

        /**
         * Creates the tile chunk.
         */
        TileChunk(sf::Vector2u size, sf::Vector2i offset);

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

    private:
        unsigned char *tiles;
};

#endif
