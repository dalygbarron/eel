#ifndef SLICE_H
#define SLICE_H

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * Represents a two dimensional slice of tile map which also has an offset in
 * the third dimension.
 */
class Slice {
    public:
        int const height;
        sf::Vector2u const size;
        std::unique_ptr<unsigned char> data;

        /**
         * Creates the slice with all it's data pre set.
         * @param height is the height offset of the slice.
         * @param size   is the width and breadth of the slice.
         */
        Slice(int height, sf::Vector2u size);
};

#endif
