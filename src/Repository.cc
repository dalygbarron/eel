#include "Repository.hh"
#include "Config.hh"
#include "Constant.hh"
#include "spdlog/spdlog.h"

Repository::Repository(Config const *config) {
    this->config = config;
    char fontFile[Constant::FILENAME_BUFFER_SIZE];
    config->inRoot(fontFile, config->get("font"));
    if (!this->font.loadFromFile(fontFile)) {
        spdlog::critical("Could not load font from file '{}'", fontFile);
        throw -1;
    }
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

sf::Font const *Repository::getFont() {
    return &this->font;
}
