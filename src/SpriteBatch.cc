#include "SpriteBatch.hh"
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "spdlog/spdlog.h"
#include "SubStream.hh"
#include "Read.hh"

#define NAME_BUFFER_SIZE 256
#define N_QUADS 50


void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= this->getTransform();
    states.texture = &(this->texture);
    target.draw(this->vertices, states);
}

SpriteBatch::SpriteBatch(char const *file) {
    spdlog::info("Loading Rat Pack '{}'", file);
    // Load in sprite data.
    sf::FileInputStream stream;
    stream.open(file);
    int32_t size = Read::readInt(&stream);
    spdlog::debug("Rat Pack Image Size: {} bytes", size);
    SubStream textureStream(&stream, size);
    if (!this->texture.loadFromStream(textureStream)) {
        spdlog::error("Loading texture in Rat pack '{}' failed.", file);
        return;
    }
    stream.seek(size + 4);
    int32_t n = Read::readInt(&stream);
    for (int i = 0; i < n; i++) {
        char name[NAME_BUFFER_SIZE];
        Read::readString(&stream, name, NAME_BUFFER_SIZE);
        int x = Read::readInt(&stream);
        int y = Read::readInt(&stream);
        int w = Read::readInt(&stream);
        int h = Read::readInt(&stream);
        spdlog::debug("Rat Pack frame '{}' ({}, {}, {}, {})", name, x, y, w, h);
        sprites[std::string(name)] = sf::IntRect(x, y, w, h);
    }
    // make vertices.
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(N_QUADS * 4);
    for (int i = 0; i < N_QUADS; i++) {
        this->vertices[i * 4 + 0].position = sf::Vector2f(i * 2, i * 16);
        this->vertices[i * 4 + 1].position = sf::Vector2f(i * 2 + 10, i * 16);
        this->vertices[i * 4 + 2].position = sf::Vector2f(i * 2 + 10, i * 16 + 10);
        this->vertices[i * 4 + 3].position = sf::Vector2f(i * 2, i * 16 + 10);
        this->vertices[i * 4 + 0].texCoords = sf::Vector2f(i * 2, i * 16);
        this->vertices[i * 4 + 1].texCoords = sf::Vector2f(i * 2 + 10, i * 16);
        this->vertices[i * 4 + 2].texCoords = sf::Vector2f(i * 2 + 10, i * 16 + 10);
        this->vertices[i * 4 + 3].texCoords = sf::Vector2f(i * 2, i * 16 + 10);
    }
}
