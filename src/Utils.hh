#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

/**
 * Contains generally helpful functions that are generally helpful without forming a profound aspect of the system.
 * This namespace should be completely free of any state, and just have some helpful bits of code in it.
 */
namespace Utils {
    // TODO: this should probably have more digits but lets wait until it wrecks something haha.
    constexpr static float const PI = 3.14159;

    /**
     * Gives the lesser of two values.
     * @param a is the first value.
     * @param b is the second value.
     * @return the lower of a and b.
     */
    float min(float a, float b);

    /**
     * Gives the greater of two values.
     * @param a is the first value.
     * @param b is the second value.
     * @return the greater of a and b.
     */
    float max(float a, float b);

    /**
     * Tells you if a given character is whitespace.
     * @param c is the character to check.
     * @return true if the character is whitespace and otherwise false.
     */
    int isWhitespace(char c);

    /**
     * Finds the end of the word that is occurring at the given offset.
     * @param string is the string to check.
     * @return the point at which the given word ends.
     */
    int endOfWord(char const *string);

    /**
     * Tells you the number of characters from the start of the string to the start of the next string.
     * @param is the string to check on.
     */
    int startOfNextWord(char const *string);

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

    /**
     * Reads a string containing a number and turns it into an int.
     * @param text is the text to read from.
     * @return the converted int.
     * @throws an exception and logs if the string is not an int.
     */
    int parseInt(char const *text);

    /**
     * Takes a set of vertices and a rectangle and sets the vertices positions to that of the rectangle.
     * @param vertices is a pointer to the four vertices to arrange.
     * @param rect     is the rectangle to make the vertices reflect.
     */
    void fitQuad(sf::Vertex *vertices, sf::FloatRect rect);

    /**
     * Takes a set of vertices and sets their colour to all the same colour.
     * @param vertices is a pointer to the four vertices to colour.
     * @param colour   is the colour to colour the quad.
     */
    void colourQuad(sf::Vertex *vertices, sf::Color colour);

    /**
     * Forms 20 vertices into a box on the screen with a nice border. The middle of the box will be the first 4
     * vertices and the rest will be the border so if you want to recolour bits it should not be too hard.
     * @param vertices   is a pointer to the vertices.
     * @param dimensions is the dimensions of the box.
     * @param border     is the thickness of the border (inside the dimensions).
     * @param fg         is the colour of the border.
     * @param bg         is the colour of the rest of the box.
     */
    void makeBox(sf::Vertex *vertices, sf::FloatRect dimensions, float border, sf::Color fg, sf::Color bg);

    /**
     * Forms 12 vertices into a box that has a border only on the top and bottom.
     * @param vertices   is a pointer to the vertices.
     * @param dimensions is the dimensions of the box.
     * @param border     is the thickness of the border (inside the dimensions).
     * @param fg         is the colour of the border.
     * @param bg         is the colour of the rest of the box.
     */
    void makeStack(sf::Vertex *vertices, sf::FloatRect dimensions, float border, sf::Color fg, sf::Color bg);

    /**
     * Forms 12 vertices into a box that has a border only on the left and right sides.
     * @param vertices   is a pointer to the vertices.
     * @param dimensions is the dimensions of the box.
     * @param border     is the thickness of the border (inside the dimensions).
     * @param fg         is the colour of the border.
     * @param bg         is the colour of the rest of the box.
     */
    void makeWall(sf::Vertex *vertices, sf::FloatRect dimensions, float border, sf::Color fg, sf::Color bg);
};

#endif
