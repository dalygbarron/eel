#include "Bullet.hh"
#include "Utils.hh"
#include <cmath>

void Bullet::copy(Bullet const *bullet) {
    this->state.live.radius = bullet->state.live.radius;
    this->state.live.speed = bullet->state.live.speed;
    this->state.live.shape = bullet->state.live.shape;
    this->state.live.sprite = bullet->state.live.sprite;
}

void Bullet::launch(float angle) {
    this->velocity.x = sin(angle) * Utils::perSecond(this->state.live.speed);
    this->velocity.y = cos(angle) * Utils::perSecond(this->state.live.speed);
}

void Bullet::gravityLaunch(float angle, float rate) {
    this->gravity.x = sin(angle) * rate;
    this->gravity.y = cos(angle) * rate;
}
