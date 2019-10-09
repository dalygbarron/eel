#ifndef CHUNK_H
#define CHUNK_H

/**
 * Represents a two dimensional square of tiles existing in three dimensional
 * space that can also have other chunks stacked on top in a linked list type
 * of deal.
 * TODO: it's all flapping in the breeze rn. When I have more brain cells think
 *       about whether all of this stuff is meant to be public.
 */
class Chunk {
    public:
        unsigned char *tiles;
        int z;
        sf::Vector2u dimensions;
        Chunk *next;

        /**
         * Creates the chunk and allocates the memory for it's tiles.
         * @param dimensions is the width and height of the chunk.
         * @param z          is the layer number this chunk is.
         */
        Chunk(sf::Vector2u dimensions, int z);

        /**
         * Destroys the tiles.
         */
        ~Chunk();

        /**
         * Stacks another chunk onto the top of the pile.
         * @param chunk is the chunk to add.
         */
        void stack(Chunk *chunk);
};

#endif
