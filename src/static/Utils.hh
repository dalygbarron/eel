#ifndef UTILS_H
#define UTILS_H

#include "static/xml/pugixml.hpp"
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
     * Tells if you if a given character is a file seperator.
     * @param c is the character to check.
     * @return true if the character is a file seperator and otherwise false.
     */
    int isSeperator(char c);

    /**
     * Makes a version of a string in a buffer that has no whitespace at the
     * start and end.
     * @param string is the string to move to the buffer.
     * @param buffer is the place to write the trimmed version.
     * @param max    is the size of the buffer.
     * @return int the length of the trimmed version.
     */
    int trimToBuffer(char const &string, char &buffer, int max);

    /**
     * Finds the end of the word that is occurring at the given offset.
     * @param string is the string to check.
     * @return the point at which the given word ends.
     */
    int endOfWord(char const &string);

    /**
     * Tells you the number of characters from the start of the string to the
     * start of the next string.
     * @param is the string to check on.
     */
    int startOfNextWord(char const &string);

    /**
     * Takes in the start point of a token in a string and then returns how
     * long that token is so you can do stuff to it easily.
     * @param start is the start of the token.
     * @return the number of characters until it ends.
     */
    int pathToken(char const &start);

    /**
     * fits some text into a given space.
     * @param string is the text to fit in.
     * @param bounds are the boundaries that the text must fit within.
     * @param text   is the text object to write it to.
     */
    void fitText(char const &string, sf::FloatRect bounds, sf::Text &text);

    /**
     * Reads in a whole file and returns it as a string.
     * @param file is the file to read in.
     * @return the whole file contents as text.
     */
    char &readFile(char const &file);

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
     * Gives the base64 representation of a character.
     * @param c is the character to parse.
     * @return the number that character represents in base 64.
     */
    unsigned int parseBase64(char c);

    /**
     * Takes a string of base64 encoded data and writes it into an array.
     * @param src is the text to read from.
     * @param dst is the data to write to.
     * @param max is the maximum number of bytes to write.
     * @return the number of bytes written.
     */
    int parseBase64String(char const &src, unsigned char &dst, int max);

    /**
     * Goes through the motions of opening up an xml file so I don't have to do
     * it every time, and if anything goes wrong it automatically logs it and
     * throws an exception.
     * @param doc    is the xml document object to set up.
     * @param tag    is the top level node that we want to find.
     * @param string is the xml file to parse in a string.
     * @return the top level node you wanted.
     */
    pugi::xml_node openXml(
        pugi::xml_document &doc,
        char const &tag,
        char const &string
    );

    /**
     * Functor to hash sf::Vector2i thingies.
     */
    struct VectHash {
        /**
         * Hashes a vector.
         * @param v is the vector to hash.
         * @return the hashed numerical value.
         */
        std::size_t operator()(sf::Vector2i const &v) const noexcept;
    };
};

#endif
