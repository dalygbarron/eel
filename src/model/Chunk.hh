#ifndef CHUNK_H
#define CHUNK_H

#include "model/Slice.hh"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Represents a three dimensional block of tile data which can have new layers
 * of data added to it.
 */
class Chunk {
    public:
        sf::Vector2u const size;

        /**
         * Create the chunk by setting the size of it's bits.
         * @param size is the size of each chunk in 2 dimensinos.
         */
        Chunk(sf::Vector2u size);

        /**
         * Gives you access to all the slices in const form. Yeah I know it's
         * pointers not references, but the only way they can be set is through
         * addSlice which requires a reference so you can be pretty sure they
         * are set I reckon. Stop whinging.
         * @return the vector of slices.
         */
        std::vector<Slice const *> const &getSlices();

        /**
         * Add a slice onto the top of all this chunk's slices.
         */
        void addSlice(Slice const &slice);

    private:
        std::vector<Slice const *> slices;
};

#endif
