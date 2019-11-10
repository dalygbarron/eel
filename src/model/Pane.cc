#include "model/Pane.hh"

void Pane::form(RatPack const &ratPack, char const &rat) {
    this->position = sf::Vector2f(0, 0);
    sf::FloatRect shape = ratPack.getRat(rat);
    this->vertices[0].position = sf::Vector2f(
        0 - shape.width / 2,
        0 - shape.height / 2
    );
    this->vertices[1].position = sf::Vector2f(
        shape.width / 2,
        0 - shape.height / 2
    );
    this->vertices[2].position = sf::Vector2f(
        shape.width / 2,
        shape.height / 2
    );
    this->vertices[3].position = sf::Vector2f(
        0 - shape.width / 2,
        shape.height / 2
    );
    this->vertices[0].texCoords = sf::Vector2f(
        shape.left,
        shape.top
    );
    this->vertices[1].texCoords = sf::Vector2f(
        shape.left + shape.width,
        shape.top
    );
    this->vertices[2].texCoords = sf::Vector2f(
        shape.left + shape.width,
        shape.top + shape.height
    );
    this->vertices[3].texCoords = sf::Vector2f(
        shape.left,
        shape.top + shape.height
    );
}

void Pane::formTile(
    RatPack const &ratPack,
    char const &rat,
    sf::Vector2u dimensions,
    int tile
) {
    this->position = sf::Vector2f(0, 0);
    sf::FloatRect shape = ratPack.getRat(rat);
    this->vertices[0].position = sf::Vector2f(
        0 - shape.width / 2,
        0 - shape.height / 2
    );
    this->vertices[1].position = sf::Vector2f(
        shape.width / 2,
        0 - shape.height / 2
    );
    this->vertices[2].position = sf::Vector2f(
        shape.width / 2,
        shape.height / 2
    );
    this->vertices[3].position = sf::Vector2f(
        0 - shape.width / 2,
        shape.height / 2
    );
    this->vertices[0].texCoords = sf::Vector2f(
        shape.left,
        shape.top
    );
    this->vertices[1].texCoords = sf::Vector2f(
        shape.left + shape.width,
        shape.top
    );
    this->vertices[2].texCoords = sf::Vector2f(
        shape.left + shape.width,
        shape.top + shape.height
    );
    this->vertices[3].texCoords = sf::Vector2f(
        shape.left,
        shape.top + shape.height
    );
}

void Pane::setPosition(sf::Vector2f pos) {
    sf::Vector2f delta = pos - this->position;
    this->addPosition(delta);
}

void Pane::addPosition(sf::Vector2f delta) {
    this->shift(delta);
    this->position += delta;
}

void Pane::shift(sf::Vector2f delta) {
    for (int i = 0; i < 4; i++) this->vertices[i].position += delta;
}

void Pane::set(sf::FloatRect shape, sf::FloatRect image) {
    this->vertices[0].position = sf::Vector2f(
        shape.left,
        shape.top
    );
    this->vertices[1].position = sf::Vector2f(
        shape.left + shape.width,
        shape.top
    );
    this->vertices[2].position = sf::Vector2f(
        shape.left + shape.width,
        shape.top + shape.height
    );
    this->vertices[3].position = sf::Vector2f(
        shape.left,
        shape.top + shape.height
    );
}

void Pane::hide() {
    for (int i = 0; i < 4; i++) {
        this->vertices[i].position = sf::Vector2f(-1, -1);
    }
    this->dirty = true;
}

Pane::Pane() {
    // very epic.
}
