#include "model/Mob.hh"

void Mob::moveTo(sf::Vertex *index) const {
    index[0] = this->vertices[0];
    index[1] = this->vertices[1];
    index[2] = this->vertices[2];
    index[3] = this->vertices[3];
}

int Mob::behind(Mob const *other) const {
    return other->position.z > this->position.z ||
        other->position.y > this->position.y;
}

sf::Vector2u Mob::sort(Mob const **mobs, int n) {
    int min = -1;
    int max = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j > 0 && mobs[j]->behind(mobs[j - 1]); j++) {
            Mob const *temp = mobs[j];
            mobs[j] = mobs[j - 1];
            mobs[j - 1] = temp;
            if (min == -1 || min > j - 1) min = j - 1;
            if (max == -1 || max < j) max = j;
        }
    }
}
