#include "BulletManager.hh"
#include "inih.hh"

int handleIni(void *manager, char const *section, char const *name, char const *value) {
    if ()

    printf("%s->%s: '%s'\n", section, name, value);
    return 1;
}

BulletManager::BulletManager(char const *file) {
    if (ini_parse(file, handleIni, this) < 0) {
        fprintf(stderr, "Could not open file %s\n", file);
        throw -1;
    }
}

void BulletManager::update() {
    for (int i = 0; i < Config::BULLET_LIMIT && this->bullets[i].alive; i++) {
        this->bullets[i].pos += this->bullets[i].velocity;
        this->bullets[i].velocity += this->bullets[i].gravity;
    }
}

void BulletManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = this->texture;
    target.draw(this->vertices, states);
}
