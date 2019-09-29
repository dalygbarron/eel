#include "model/Bullet.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <cmath>

void Bullet::copy(Bullet const *bullet) {
    if (!this->alive) {
        // Must not copy to dead bullet as it could corrupt the lazy list.
        spdlog::critical("Trying to copy to dead bullet.");
        throw -1;
    }
    this->state.live.radius = bullet->state.live.radius;
    this->state.live.shape = bullet->state.live.shape;
    this->state.live.sprite = bullet->state.live.sprite;
    this->state.live.speed = bullet->state.live.speed;
}

void Bullet::launch(float angle) {
    this->velocity.x = sin(angle) * this->state.live.speed;
    this->velocity.y = cos(angle) * this->state.live.speed;
}

void Bullet::gravityLaunch(float angle, float rate) {
    this->gravity.x = sin(angle) * rate;
    this->gravity.y = cos(angle) * rate;
}
