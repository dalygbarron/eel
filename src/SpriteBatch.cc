#include "SpriteBatch.hh"
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Read.hh"


void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &(this->texture);
    target.draw(this->vertices, states);
}

SpriteBatch::SpriteBatch(char const *file) {
    sf::FileInputStream stream;
    stream.open(file);
    int32_t size = Read::readInt(&stream);
    if (!this->texture.loadFromStream(stream)) {
        fprintf(stderr, "Loading texture from rat pack '%s' did not work.\n", file);
        throw -1;
    }
    int32_t n = Read::readInt(&stream);
    for (int i = 0; i < n; i++) {


    }
}
