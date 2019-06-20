#include "Repository.hh"
#include "Config.hh"
#include "Constant.hh"

Repository::Repository(Config const *config) {
    this->config = config;
}

sf::Texture *Repository::getTexture(char const *name) {

}

SpriteBatch *Repository::getSpriteBatch(char const *name) {
    try {
        return this->spriteBatches.at(name);
    } catch (...) {
        char filename[Constant::FILENAME_BUFFER_SIZE];
        this->config->inRoot(filename, name);
        SpriteBatch *spriteBatch = new SpriteBatch(filename);
        this->spriteBatches[name] = spriteBatch;
        return spriteBatch;
    }
}
