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

sf::FloatRect RatPack::getRat(char const &name) const {
    if (!this->rats.count(&name)) {
        spdlog::warn("Rat pack lacks '{}'", &name);
        return sf::FloatRect(0, 0, 0, 0);
    }
    return this->rats.at(&name);
}

void RatPack::addRat(char const &name, sf::FloatRect shape) {
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
