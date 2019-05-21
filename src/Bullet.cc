#include "Bullet.hh"
#include <cmath>

void Bullet::launch(float angle, float speed) {
    this->velocity.x = sin(angle) * speed;
    this->velocity.y = cos(angle) * speed;
}

void Bullet::gravityLaunch(float angle, float speed) {
    this->gravity.x = sin(angle) * speed;
    this->gravity.y = cos(angle) * speed;
}
