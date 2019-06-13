#include "BulletManager.hh"
#include "spdlog/spdlog.h"
#include "inih.hh"
#include "Repository.hh"
#include "Config.hh"

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= this->getTransform();
    states.texture = this->sprites;
    target.draw(this->vertices, states);
}

BulletManager::BulletManager(Game const *game, Repository *repository): Store("Bullet Manager") {
    this->game = game;
    this->repository = repository;
    char file[Config::FILENAME_BUFFER_SIZE];
    game->inRoot(file, game->get(Config::BULLET_FILE));
    // Load in the bullet info.
    spdlog::info("Loading bullets from '{}'", file);
    if (ini_parse(file, BulletManager::handleIni, this) < 0) {
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
    // Create the vertices.
    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(Config::BULLET_LIMIT * 4);
}

void BulletManager::update() {
    for (int i = 0; i < Config::BULLET_LIMIT && this->bullets[i].alive; i++) {
        this->bullets[i].pos += this->bullets[i].velocity;
        this->bullets[i].velocity += this->bullets[i].gravity;
        for (int v = 0; v < 4; v++) {
            this->vertices[i * 4 + v].position += this->bullets[i].velocity;
        }
    }
}

Bullet const *BulletManager::getPrototype(char const *type) {
    return this->get(type);
}

Bullet *BulletManager::addBullet(Bullet const *prototype, sf::Vector2f position) {
    // TODO: potentially you could create a bullet and then it could be destroyed and then another created bullet could
    //       take it's spot in the pool all while you have the same pointer to that bullet thinking it is the old
    //       bullet. Therefore, whenever a bullet is created it would be a good idea to store the current time in it or
    //       something which can be recorded so that you know that the pointer you have is pointing to the bullet you
    //       think it is pointing to.
    if (!this->empty) {
        spdlog::debug("Trying to add bullet to full pool");
        return 0;
    } else {
        Bullet *newBullet = this->empty;
        this->empty = this->empty->state.next;
        newBullet->alive = true;
        newBullet->copy(prototype);
        newBullet->pos = position;
        newBullet->velocity.x = 0.5;
        newBullet->velocity.y = 0.92;
        this->sprites->buildQuad(
            &(this->vertices[(newBullet - this->bullets) * 4]),
            prototype->state.live.sprite,
            position,
            0
        );
        return newBullet;
    }
}

int BulletManager::handleIni(void *reference, char const *section, char const *name, char const *value) {
    BulletManager *manager = (BulletManager *)reference;
    if (!section[0]) {
        // Configuration settings.
        if (strcmp(name, "spritesheet") == 0) {
            manager->sprites = manager->repository->getSpriteBatch(value);
        } else {
            spdlog::warn("'{}': '{}' is not a known configuration setting in bullets ini.", name, value);
        }
    } else {
        // Bullet params.
        Bullet *prototype = manager->getSafely(section, 0);
        if (!prototype) {
            prototype = new Bullet();
            manager->store(section, prototype);
        }
        if (strcmp(name, "sprite") == 0) {
            int nameLength = strlen(value);
            prototype->state.live.sprite = new char[nameLength];
            strcpy(prototype->state.live.sprite, value);
        } else if (strcmp(name, "shape") == 0) {
            prototype->state.live.shape = strtol(value, 0, 0);
        } else if (strcmp(name, "radius") == 0) {
            prototype->state.live.radius = strtol(value, 0, 0);
        } else if (strcmp(name, "speed") == 0) {
            prototype->state.live.speed = strtol(value, 0, 0);
        } else {
            spdlog::warn("[{}] '{}': '{}' is not a known parameter of bullets in bullets ini.", section, name, value);
        }
    }
    return 1;
}
