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

void Tileset::buildQuad(sf::Vertex *vertices, unsigned char id) const {

}

void Tileset::apply(sf::Texture *atlas) const {
    sf::Vector2u size = this->texture->get()->getSize();
    if (size.x > Constant::TILESET_MAX_WIDTH ||
        size.y > Constant::TILESET_MAX_HEIGHT) {
        spdlog::warn(
            "Tileset '{}' must fit ({}, {}) for texture atlas. is ({}, {})",
            this->name,
            Constant::TILESET_MAX_WIDTH,
            Constant::TILESET_MAX_HEIGHT,
            size.x,
            size.y
        );
        return;
    }
    atlas->update(*(this->texture->get()));
}
