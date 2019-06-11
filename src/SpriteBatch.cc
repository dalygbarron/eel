#include "SpriteBatch.hh"
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "spdlog/spdlog.h"
#include "SubStream.hh"
#include "Read.hh"

#define NAME_BUFFER_SIZE 256


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
    this->vertices.resize(n * 2 * 4);
    int i = 0;
    for (auto const &pair: this->sprites) {
        this->vertices[i * 8 + 0].position = sf::Vector2f(i, i * 16);
        this->vertices[i * 8 + 1].position = sf::Vector2f(i + pair.second.width, i * 16);
        this->vertices[i * 8 + 2].position = sf::Vector2f(i + pair.second.width, i * 16 + pair.second.height);
        this->vertices[i * 8 + 3].position = sf::Vector2f(i, i * 16 + pair.second.height);
        this->vertices[i * 8 + 0].texCoords = sf::Vector2f(pair.second.left, pair.second.top);
        this->vertices[i * 8 + 1].texCoords = sf::Vector2f(pair.second.left + pair.second.width, pair.second.top);
        this->vertices[i * 8 + 2].texCoords = sf::Vector2f(pair.second.left + pair.second.width, pair.second.top + pair.second.height);
        this->vertices[i * 8 + 3].texCoords = sf::Vector2f(pair.second.left, pair.second.top + pair.second.height);
        this->vertices[i * 8 + 4].position = sf::Vector2f(i + 50, i * 16);
        this->vertices[i * 8 + 5].position = sf::Vector2f(i + 50 + pair.second.width, i * 16);
        this->vertices[i * 8 + 6].position = sf::Vector2f(i + 50 + pair.second.width, i * 16 + pair.second.height);
        this->vertices[i * 8 + 7].position = sf::Vector2f(i + 50, i * 16 + pair.second.height);
        this->vertices[i * 8 + 4].texCoords = sf::Vector2f(pair.second.left, pair.second.top);
        this->vertices[i * 8 + 5].texCoords = sf::Vector2f(pair.second.left + pair.second.width, pair.second.top);
        this->vertices[i * 8 + 6].texCoords = sf::Vector2f(pair.second.left + pair.second.width, pair.second.top + pair.second.height);
        this->vertices[i * 8 + 7].texCoords = sf::Vector2f(pair.second.left, pair.second.top + pair.second.height);
        i++;
    }
}
