#ifndef SUB_STREAM_H
#define SUB_STREAM_H

#include <SFML/System.hpp>

/**
 * An input stream that is just a portion of another input stream.
 */
class SubStream: public sf::InputStream {
    InputStream *mother;
    int size;
    int start;
    int cursor;

public:
    /**
     * Creates the sub stream from the big stream.
     * @param mother is the bigger stream this one is cutting from.
     * @param size   is how much data from the mother stream that this one should take.
     */
    SubStream(sf::InputStream *mother, int size);

    virtual sf::Int64 read(void *data, sf::Int64 size) override;

    virtual sf::Int64 seek(sf::Int64 position) override;

    virtual sf::Int64 tell() override;

    virtual sf::Int64 getSize() override;
};

#endif
