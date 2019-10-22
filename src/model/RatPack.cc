#include "model/RatPack.hh"

RatPack::RatPack(sf::Texture *texture) {
    this->texture = texture;
}

sf::Texture *RatPack::getTexture() {
    return this->texture;
}

void RatPack::makeRat(char const *name, sf::Vertex *vertices) const {
    sf::IntRect rat = this->rats[name];
    vertices[0].position = sf::Vertex2f(0 - rat.w / 2, 0 - rat.h / 2);
    vertices[1].position = sf::Vertex2f(rat.w / 2, 0 - rat.h / 2);
    vertices[2].position = sf::Vertex2f(rat.w / 2, rat.h / 2);
    vertices[3].position = sf::Vertex2f(0 - rat.w / 2, rat.h / 2);
}

void RatPack::addRat(char const *name, sf::IntRect shape) {
    if (this->rats.count(name)) {
        spdlog::warn("Name '{}' is duplicated in rat pack", name);
    }
    spdlog::debug(
        "Adding new rat '{}' ({}, {}, {}, {})",
        name,
        shape.x,
        shape.y,
        shape.w,
        shape.h
    );
    this->rats[name] = shape;
}
