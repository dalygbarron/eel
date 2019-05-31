#include "Read.hh"
#include <stdint.h>
#include <SFML/System.hpp>


int32_t Read::readInt(sf::InputStream *stream) {
    int32_t total = 0;
    for (int i = 0; i < 4; i++) {
        int input;
        stream->read(&input, 1);
        total <<= 8;
        total |= (input & 0xff);
    }
    return total;
}

void Read::readString(sf::InputStream *stream, char *buffer, int n) {
    int count = stream->read(buffer, n);
    for (int i = 0; i < count; i++) {
        if (!buffer[i]) {
            stream->seek(stream->tell() - (count - i));
            return;
        }
    }
    fprintf(stderr, "Hit buffer end.\n");
    buffer[n - 1] = 0;
}

char *Read::readString(sf::InputStream *stream) {
    // TODO: implement this when needed if ever.
    return 0;
}
