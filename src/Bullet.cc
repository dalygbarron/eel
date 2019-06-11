#include "Bullet.hh"
#include <cmath>

void Bullet::copy(Bullet const *bullet) {
    this->state.live.radius = bullet->state.live.radius;
    this->state.live.speed = bullet->state.live.speed;
    this->state.live.shape = bullet->state.live.shape;
    this->state.live.sprite = bullet->state.live.sprite;
}

void Bullet::launch(float angle, float speed) {
    this->velocity.x = sin(angle) * speed;
    this->velocity.y = cos(angle) * speed;
}

void Bullet::gravityLaunch(float angle, float speed) {
    this->gravity.x = sin(angle) * speed;
    this->gravity.y = cos(angle) * speed;
}
