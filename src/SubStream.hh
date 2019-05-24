#ifndef SUB_STREAM_H
#define SUB_STREAM_H

#include <SFML/System.hpp>

/**
 * An input stream that is just a portion of another input stream.
 */
class SubStream: public sf::InputStream {
    InputStream *mother;
    int size;
    int cursor;
    int start;

public:
    /**
     * Creates the sub stream from the big stream.
     * @param mother is the bigger stream this one is cutting from.
     * @param size   is how much data from the mother stream that this one should take.
     */
    SubStream(sf::InputStream *mother, int size);

    virtual Int64 read(void *data, Int64 size) override;

    virtual Int64 seek(Int64 position) override;

    virtual Int64 tell() override;

    virtual Int64 getSize() override;
};

#endif
