#include "Read.hh"
#include <stdint.h>
#include <SFML/System.hpp>


int32_t Read::readInt(sf::InputStream *stream) {
    int32_t total = 0;
    for (int i = 0; i < 4; i++) {
        char input;
        stream->read(&input, 1);
        total <<= 8;
        total |= input;
    }
    return total;
}

void Read::readString(sf::InputStream *stream, char *buffer, int n) {

}

char *Read::readString(sf::InputStream *stream) {

}
