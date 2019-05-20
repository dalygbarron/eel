#include "BulletManager.hh"

BulletManager::BulletManager(char const *file) {

}

void BulletManager::update() {
    for (int i = 0; i < Config::BULLET_LIMIT && this->bullets[i]->alive; i++) {
        this->bullets[i].pos += this->bullets[i].velocity;
        this->bullets[i].velocity += this->bullets[i].gravity;
    }
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = this->texture;
    target.draw(this->vertices, states);
}
