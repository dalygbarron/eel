#include "model/RatPack.hh"

RatPack::RatPack(Asset<sf::Texture> const *texture) {
    this->texture = texture;
}

void RatPack::makeRat(char const *name, sf::Vertex *vertices) {
    sf::IntRect rat = this->rats[name];
    vertices[0].position = sf::Vertex2f(0 - rat.w / 2, 0 - rat.h / 2);
}

void RatPack::addRat(char const *name, sf::IntRect shape) {
    if (this->rats.count(name)) {
        spdlog::warn("Name '{}' is duplicated in rat pack", name);
    }
    this->rats[name] = shape;
}
