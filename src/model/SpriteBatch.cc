#include "model/SpriteBatch.hh"
#include "model/SubStream.hh"
#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include "service/Config.hh"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdint.h>

SpriteBatch::SpriteBatch(char const *file) {
    // TODO: load in all the shit.
}

void SpriteBatch::buildQuad(
    sf::Vertex *vertices,
    char const *spriteName,
    sf::Vector2f position,
    float angle,
    float scale
) {
    sf::IntRect sprite = this->get(spriteName);
    vertices[0].position = position + sf::Vector2f(-sprite.width / 2, -sprite.height / 2) * scale;
    vertices[1].position = position + sf::Vector2f(sprite.width / 2, -sprite.height / 2) * scale;
    vertices[2].position = position + sf::Vector2f(sprite.width / 2, sprite.height / 2) * scale;
    vertices[3].position = position + sf::Vector2f(-sprite.width / 2, sprite.height / 2) * scale;
    vertices[0].texCoords = sf::Vector2f(sprite.left, sprite.top);
    vertices[1].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top);
    vertices[2].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top + sprite.height);
    vertices[3].texCoords = sf::Vector2f(sprite.left, sprite.top + sprite.height);
}

void SpriteBatch::moveQuad(sf::Vertex *vertices, sf::Vector2f position) {
    float width = (vertices[1].position.x - vertices[0].position.x) / 2;
    float height = (vertices[2].position.y - vertices[1].position.y) / 2;
    vertices[0].position = position + sf::Vector2f(-width, -height);
    vertices[1].position = position + sf::Vector2f(width, -height);
    vertices[2].position = position + sf::Vector2f(width, height);
    vertices[3].position = position + sf::Vector2f(-width, height);
}

void SpriteBatch::fitQuad(sf::Vertex *vertices, char const *spriteName) {
    // TODO: make this safe.
    sf::IntRect sprite = this->get(spriteName);
    vertices[0].texCoords = sf::Vector2f(sprite.left, sprite.top);
    vertices[1].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top);
    vertices[2].texCoords = sf::Vector2f(sprite.left + sprite.width, sprite.top + sprite.height);
    vertices[3].texCoords = sf::Vector2f(sprite.left, sprite.top + sprite.height);
}
