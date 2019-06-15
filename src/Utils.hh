#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

/**
 * Contains generally helpful functions that are generally helpful without forming a profound aspect of the system.
 */
namespace Utils {
    /**
     * Wraps a vector around inside a rect.
     * @param pos    is a position to be fitted inside the rectangle.
     * @param bounds is the bounds within which the position is wrapped around.
     * @return the wrapped version of the vector.
     */
    sf::Vector2f wrapped(sf::Vector2f pos, sf::FloatRect bounds);

    /**
     * Gives a random number from 0 to 1 inclusive.
     * @return the random number I just described.
     */
    float random();
};

#endif
