#include "SpriteBatch.hh"
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SubStream.hh"
#include "Read.hh"

#define NAME_BUFFER_SIZE 256


void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &(this->texture);
    target.draw(this->vertices, states);
}

SpriteBatch::SpriteBatch(char const *file) {
    sf::FileInputStream stream;
    stream.open(file);
    int32_t size = Read::readInt(&stream);
    SubStream textureStream(&stream, size);
    if (!this->texture.loadFromStream(textureStream)) {
        fprintf(stderr, "Loading texture from rat pack '%s' did not work.\n", file);
        throw -1;
    }
    stream.seek(size + 4);
    int32_t n = Read::readInt(&stream);
    for (int i = 0; i < n; i++) {
        char name[NAME_BUFFER_SIZE];
        Read::readString(&stream, name, NAME_BUFFER_SIZE);
        printf("name %s\n", name);
        int x = Read::readInt(&stream);
        int y = Read::readInt(&stream);
        int w = Read::readInt(&stream);
        int h = Read::readInt(&stream);
        printf("%d, %d, %d, %d\n", x, y, w, h);
        sprites[std::string(name)] = sf::IntRect(x, y, w, h);
    }
}
