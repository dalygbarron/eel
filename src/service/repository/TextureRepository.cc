#include "service/repository/TextureRepository.hh"

TextureRepository::TextureRepository(Config const *config) {
    this->config = config;
}

sf::Texture *TextureRepository::create(char const *name) {
    spdlog::info("create texture: '{}'", name);
    char filename[Constant::FILENAME_BUFFER_SIZE];
    this->config->inRoot(filename, name);
    sf::Texture *texture = new sf::Texture();
    if (!texture->loadFromFile(filename)) {
        spdlog::error("Cannot load texture at '{}'", filename);
    } else {
        texture->setSmooth(true);
        texture->setRepeated(true);
        this->textures[name] = texture;
        return texture;
    }
}
