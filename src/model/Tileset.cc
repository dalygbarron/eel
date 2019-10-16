#include "model/Tileset.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <climits>

Tileset::Tileset(
    char const *name,
    sf::Vector2u tileSize,
    Asset<sf::Texture> const *texture
) {
    this->name = name;
    this->tileSize = tileSize;
    this->texture = texture;
}

Tileset::~Tileset() {
    delete this->name;
}

char const *Tileset::getName() const {
    return this->name;
}

sf::Vector2u Tileset::getTileSize() const {
    return this->tileSize;
}

Asset<sf::Texture> const *Tileset::getTexture() const {
    return this->texture;
}

void Tileset::buildQuad(sf::Vertex *vertices, unsigned char id) const {

}
