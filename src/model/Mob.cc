#include "model/Mob.hh"
#include "static/Constant.hh"

void Mob::attach(Pane *pane) {
    this->pane = pane;
}

void Mob::place(sf::Vector3f pos) {
    this->position = pos;
    if (pane) {
        this->index = pos.y;
        // TODO: 32 will simply have to be a constant :/
        sf::Vector2f move(
            pos.x * 32 - pos.y * 32,
            (pos.x * 32 + pos.y * 32) / 2 - pos.z * 32
        );
        this->pane->setPosition(move);
    }
}
