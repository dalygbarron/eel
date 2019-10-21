#include "model/Rat.hh"

Rat(sf::Vertex *vertices) {
    this->vertices = vertices;
}

sf::Vector2f getPosition() {
    return this->position;
}

void setPosition(sf::Vector2f position) {
    this->addPosition(position - this->position);
}

void addPosition(sf::Vector2f delta) {
    for (int i = 0; i < 4; i++) vertices[i].position += delta;
    this->position += delta;
}
