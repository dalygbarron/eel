#include "model/Mob.hh"

void Mob::attach(Pane *pane) {
    this->pane = pane;
}

void Mob::place(sf::Vector3f pos) {
    this->position = pos;
    if (pane) {
        order = pos.y;
        Vector2f move(
            (pos.x - pos.z) / Constant::SQUARE_ROOT_OF_TWO,
            (pos.x + 2 * pos.y + pos.z) / SQUARE_ROOT_OF_SIX
        );
        this->pane->move(move);
    }
}
