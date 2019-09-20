#include "src/model/Mob.hh"

void Mob::moveTo(sf::Vertex *index) const {
    index[0] = this->vertices[0];
    index[1] = this->vertices[1];
    index[2] = this->vertices[2];
    index[3] = this->vertices[3];
}

int Mob::behind(Mob *other) const {
    return other.position.z > this->position.z ||
        other.position.y > this->position.y;
}
