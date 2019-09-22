#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

/**
 * Contains generally helpful functions that are generally helpful without
 * forming a profound aspect of the system. This namespace should be completely
 * free of any state, and just have some helpful bits of code in it.
 */
namespace Utils {
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
     * Tells you the number of characters from the start of the string to the
     * start of the next string.
     * @param is the string to check on.
     */
    int startOfNextWord(char const *string);

    /**
     * fits some text into a given space.
     * @param string is the text to fit in.
     * @param bounds are the boundaries that the text must fit within.
     * @param text   is the text object to write it to.
     */
    void fitText(char const *string, sf::FloatRect bounds, sf::Text *text);

    /**
     * Reads in a whole file and returns it as a string.
     * @param file is the file to read in.
     * @return the whole file contents as text.
     */
    char *readFile(char const *file);

    /**
     * Moves a string into a new piece of memory that fits it. Useful if the
     * passed string is going to be deleted by some other code.
     * @param string is the string to make a copy of.
     * @return a pointer to the new string.
     */
    char *moveString(char const *string);

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
     * Gives a view that will maintain the game's aspect ratio when resizing.
     * @param view         is the view as it has been changed.
     * @param dimensions is a vector of the window dimensions.
     * @return the new letterboxed version of the view.
     */
    sf::View getLetterboxView(sf::View view, sf::Vector2i dimensions);

    /**
     * Reads a string containing a number and turns it into an int.
     * @param text is the text to read from.
     * @return the converted int.
     * @throws an exception and logs if the string is not an int.
     */
    int parseInt(char const *text);

    /**
     * Takes a set of vertices and a rectangle and sets the vertices positions
     * to that of the rectangle.
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
};

#endif
