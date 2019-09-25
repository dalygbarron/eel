#ifndef TILE_CHUNK_H
#define TILE_CHUNK_H

/**
 * Represents a chunk of tiles within a tile map.
 */
class TileChunk {
    public:
        /**
         * Creates the tile chunk.
         */
        TileChunk(sf::Vector2u size, sf::Vector2i offset);

    private:
        sf::Vector2u size;
        sf::Vector2i offset;
        unsigned char *tiles;
}

#endif
