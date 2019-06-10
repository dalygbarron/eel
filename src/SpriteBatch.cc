#include "SpriteBatch.hh"
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "spdlog/spdlog.h"
#include "SubStream.hh"
#include "Read.hh"

#define NAME_BUFFER_SIZE 256


void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &(this->texture);
    target.draw(this->vertices, states);
}

SpriteBatch::SpriteBatch(char const *file): vertices(sf::Triangles, Config::BULLET_LIMIT) {
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
    for (int i = 0; i < Config::BULLET_LIMIT; i++) {
        this->vertices[i * 3 + 0].position = sf::Vector2f(i, i * - 3);
        this->vertices[i * 3 + 1].position = sf::Vector2f(i + 5, i * 2 + 3);
        this->vertices[i * 3 + 2].position = sf::Vector2f(i + 10, i * 2 + 9);
        this->vertices[i * 3 + 0].color = sf::Color::Red;
        this->vertices[i * 3 + 1].color = sf::Color::Green;
        this->vertices[i * 3 + 2].color = sf::Color::Blue;
    }
}
