#include "model/Mob.hh"
#include "static/Utils.hh"

void Mob::attach(Pane *pane) {
    this->pane = pane;
}

void Mob::place(sf::Vector3f pos) {
    this->position = pos;
    if (pane) {
        this->pane->index = pos.y;
        this->pane->setPosition(Utils::screenPosition(pos));
    }
}

void Mob::update(float delta) {
    this->position += sf::Vector3f(
        velocity.x * delta,
        velocity.y * delta,
        velocity.z * delta
    );
    if (pane) {
        this->pane->index = this->position.y;
        this->pane->setPosition(Utils::screenPosition(this->position));
    }
}
