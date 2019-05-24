#ifndef READ_H
#define READ_H

#include <stdint.h>
#include <SFML/System.hpp>

/**
 * set of functions for reading stuff out of sfml input streams without endianness problems and such.
 */
namespace Read {
    /**
     * Reads a big endian 4 byte int in from an input stream.
     * @param stream is the stream to read from.
     * @return the read int.
     */
    int32_t readInt(sf::InputStream *stream);

    /**
     * Reads a string from an input stream into a buffer.
     * @param stream is the stream from which to read.
     * @param buffer is the character buffer to write the string into.
     * @param n      is the maximum amount of text to read in.
     */
    void readString(sf::InputStream *stream, char *buffer, int n);

    /**
     * Reads a string from an input stream into a freshly made piece of memory fitted to it.
     * @param stream is the stream to read from.
     * @return pointer to the new null terminated string.
     */
    char *readString(sf::InputStream *stream);
};

#endif
