#include "model/Mob.hh"
#include "static/Utils.hh"

void Mob::attach(Pane *pane) {
    this->pane = pane;
}

void Mob::place(sf::Vector3f pos) {
    this->position = pos;
    if (pane) {
        sf::Vector2f screenPos = Utils::screenPosition(pos);
        this->pane->index = screenPos.y + pos.z;
        this->pane->setPosition(screenPos);
    }
}

void Mob::update(float delta) {
    this->position += sf::Vector3f(
        velocity.x * delta,
        velocity.y * delta,
        velocity.z * delta
    );
    if (pane) {
        sf::Vector2f screenPos = Utils::screenPosition(this->position);
        this->pane->index = screenPos.y + this->position.z;
        this->pane->setPosition(screenPos);
    }
}
