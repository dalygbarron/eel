#ifndef SLICE_H
#define SLICE_H

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * Represents a two dimensional slice of tile map which also has an offset in
 * the third dimension. You will notice the data is public and mutable, and
 * that is because you should be passing this as a const if you don't want
 * people fucking with it as you often won't.
 */
class Slice {
    public:
        int const height;
        sf::Vector2u const size;
        unsigned char *data;

        /**
         * Creates the slice with all it's data pre set.
         * @param height is the height offset of the slice.
         * @param size   is the width and breadth of the slice.
         */
        Slice(int height, sf::Vector2u size);

        /**
         * Deletes the slice's internal data.
         */
        ~Slice();
};

#endif
