#include "Repository.hh"

Repository::Repository(Game const *game) {
    this->game = game;
}

sf::Texture *Repository::getTexture(char const *name) {

}

SpriteBatch *Repository::getSpriteBatch(char const *name) {
    try {
        return this->spriteBatches.at(name);
    } catch (...) {
        char filename[Config::FILENAME_BUFFER_SIZE];
        this->game->inRoot(filename, name);
        SpriteBatch *spriteBatch = new SpriteBatch(filename);
        this->spriteBatches[name] = spriteBatch;
        return spriteBatch;
    }
}
