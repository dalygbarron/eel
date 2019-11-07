#include "model/Pane.hh"

void Pane::setPosition(sf::Vector2f pos) {
    sf::Vector2f delta = pos - this->position;
    this->addPosition(delta);
}

void Pane::addPosition(sf::Vector2f delta) {
    if (this->vertices) {
        for (int i = 0; i < 4; i++) this->vertices[i].position += delta;
    }
    this->position += delta;
}

void Pane::hide() {
    for (int i = 0; i < 4; i++) {
        this->vertices[i].position = sf::Vector2f(-1, -1);
    }
    this->dirty = true;
}
