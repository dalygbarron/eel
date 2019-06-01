#include "BulletManager.hh"
#include "spdlog/spdlog.h"
#include "inih.hh"


int handleIni(void *reference, char const *section, char const *name, char const *value) {
    BulletManager *manager = (BulletManager *)reference;
    if (!section[0]) {
        // Configuration settings.
        if (strcmp(name, "spritesheet") == 0) {
            manager->sprites = new SpriteBatch(value);
        } else {
            spdlog::warn("'{}': '{}' is not a known configuration setting in bullets ini.", name, value);
        }
    } else {
        // Bullet specifications.
    }
    return 1;
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*(this->sprites));
}

BulletManager::BulletManager(char const *file) {qw2
    // Load in the bullet info.
    spdlog::info("Loading bullets from '{}'", file);
    if (ini_parse(file, handleIni, this) < 0) {
        spdlog::error("Could not open file '{}'", file);
        throw -1;
    }
    // Init the bullets to nothing.
    for (int i = 0; i < Config::BULLET_LIMIT - 1; i++) {
        this->bullets[i].alive = false;
        this->bullets[i].state.next = this->bullets + i + 1;
    }
    this->bullets[Config::BULLET_LIMIT - 1].alive = false;
    this->bullets[Config::BULLET_LIMIT - 1].state.next = 0;
    this->empty = this->bullets;
}

void BulletManager::update() {
    for (int i = 0; i < Config::BULLET_LIMIT && this->bullets[i].alive; i++) {
        this->bullets[i].pos += this->bullets[i].velocity;
        this->bullets[i].velocity += this->bullets[i].gravity;
    }
}

Bullet const *BulletManager::getPrototype(char const *type) {
    Bullet *prototype = this->prototypes[type];
    if (prototype) {
        return prototype;
    } else {
        spdlog::error("No bullet prototype called '{}'", type);
        return 0;
    }
}

Bullet *BulletManager::addBullet(Bullet const *prototype, sf::Vector2f position) {
    if (!this->empty) {
        spdlog::debug("Trying to add bullet to full pool");
        return 0;
    } else {
        Bullet *newBullet = this->empty;
        this->empty = this->empty->state.next;
        newBullet->alive = true;
        newBullet->copy(prototype);
        newBullet->pos = position;
    }
}
