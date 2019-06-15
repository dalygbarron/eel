#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

/**
 * Contains generally helpful functions that are generally helpful without forming a profound aspect of the system.
 * This namespace should be completely free of any state, and just have some helpful bits of code in it.
 */
namespace Utils {
    constexpr float const PI = 3.14159;

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

    /**
     * Converts a per second value into per frame using the framerate.
     * @param value is the value to convert.
     * @return the given value as being per frame rather than per second.
     */
    float perSecond(float value);

    /**
     * Converts a per second per second value into per frame using the config framerate. This kind of value
     * is commonly used for calculating accelerations and other things like that.
     * @param value is the value to convert.
     * @return the given value as being per frame rather than per second per second.
     */
    float perSecondPerSecond(float value);

    /**
     * Gives a view that will maintain the game's aspect ratio when resizing.
     * @param view         is the view as it has been changed.
     * @param windowWidth  is the width of the original window.
     * @param windowHeight is the height of the original window.
     * @return the new letterboxed version of the view.
     */
    sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
};

#endif
