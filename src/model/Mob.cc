#include "model/Mob.hh"
#include "static/Constant.hh"

void Mob::attach(Pane *pane) {
    this->pane = pane;
}

void Mob::place(sf::Vector3f pos) {
    this->position = pos;
    if (pane) {
        this->index = pos.y;
        sf::Vector2f move(
            (pos.x - pos.z) / Constant::SQUARE_ROOT_OF_TWO,
            (pos.x + 2 * pos.y + pos.z) / Constant::SQUARE_ROOT_OF_SIX
        );
        this->pane->setPosition(move);
    }
}
