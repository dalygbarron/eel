#include "Repository.hh"

sf::Texture *Repository::getTexture(char const *name) {

}

SpriteBatch *Repository::getSpriteBatch(char const *name) {

}

BulletManager *Repository::getBulletManager(char const *name) {
    static BulletManager bulletManager(name);
    return &bulletManager;
}
