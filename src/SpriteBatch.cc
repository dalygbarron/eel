#include "SpriteBatch.hh"
#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "spdlog/spdlog.h"
#include "SubStream.hh"
#include "Read.hh"

#define NAME_BUFFER_SIZE 256

SpriteBatch::SpriteBatch(char const *file): Store(file) {
    spdlog::info("Loading Rat Pack '{}'", file);
    // Load in sprite data.
    sf::FileInputStream stream;
    stream.open(file);
    int32_t size = Read::readInt(&stream);
    spdlog::debug("Rat Pack Image Size: {} bytes", size);
    SubStream textureStream(&stream, size);
    if (!this->loadFromStream(textureStream)) {
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
        this->store(name, sf::IntRect(x, y, w, h));
    }
}

void SpriteBatch::buildQuad(sf::Vertex *vertices, char const *spriteName, sf::Vector2f position, float angle) {
    sf::IntRect sprite = this->get(spriteName);
    vertices[0].position = position;
    vertices[1].position = position + sf::Vector2f(sprite.width, 0);
    vertices[2].position = position + sf::Vector2f(sprite.width, sprite.height);
    vertices[3].position = position + sf::Vector2f(0, sprite.height);
    vertices[0].texCoords = sf::Vector2f(sprite.left, sprite.top);
    vertices[1].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top);
    vertices[2].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top + sprite.height);
    vertices[3].texCoords = sf::Vector2f(sprite.left, sprite.top + sprite.height);
}

void SpriteBatch::fitQuad(sf::Vertex *vertices, char const *spriteName) {
    // TODO: make this safe.
    sf::IntRect sprite = this->get(spriteName);
    vertices[0].texCoords = sf::Vector2f(sprite.left, sprite.top);
    vertices[1].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top);
    vertices[2].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top + sprite.height);
    vertices[3].texCoords = sf::Vector2f(sprite.left, sprite.top + sprite.height);
}
