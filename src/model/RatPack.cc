#include "model/RatPack.hh"
#include "static/spdlog/spdlog.h"

RatPack::RatPack(sf::Texture &texture): texture(texture) {
    // does nothing atm.
}

sf::Texture const &RatPack::getTexture() const {
    return this->texture;
}

sf::Texture &RatPack::getTextureMutable() {
    return this->texture;
}

void RatPack::makeRat(char const &name, sf::Vertex &vertices) const {
    sf::IntRect rat = this->rats.at(&name);
    sf::Vertex *vertexPointer = &vertices;
    vertexPointer[0].position = sf::Vector2f(0 - rat.width / 2, 0 - rat.height / 2);
    vertexPointer[1].position = sf::Vector2f(rat.width / 2, 0 - rat.height / 2);
    vertexPointer[2].position = sf::Vector2f(rat.width / 2, rat.height / 2);
    vertexPointer[3].position = sf::Vector2f(0 - rat.width / 2, rat.height / 2);
}

sf::IntRect RatPack::getRat(char const &name) const {
    if (!this->rats.count(&name)) {
        spdlog::warn("Rat pack lacks '{}'", &name);
        return sf::IntRect(0, 0, 0, 0);
    }
    return this->rats.at(&name);
}

void RatPack::addRat(char const &name, sf::IntRect shape) {
    if (this->rats.count(&name)) {
        spdlog::warn("Name '{}' is duplicated in rat pack", &name);
    }
    spdlog::debug(
        "Adding new rat '{}' ({}, {}, {}, {})",
        &name,
        shape.left,
        shape.top,
        shape.width,
        shape.height
    );
    this->rats[&name] = shape;
}
