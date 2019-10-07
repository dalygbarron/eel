#include "service/repository/TextureRepository.hh"
#include "static/spdlog/spdlog.h"

sf::Texture *TextureRepository::create(char const *filename) {
    spdlog::info("create texture: '{}'", filename);
    sf::Texture *texture = new sf::Texture();
    if (texture->loadFromFile(filename)) {
        texture->setSmooth(true);
        texture->setRepeated(true);
        return texture;
    }
    spdlog::error("could nto laod texture at '{}'", filename);
    return 0;
}
