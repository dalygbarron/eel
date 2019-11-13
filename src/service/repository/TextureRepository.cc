#include "service/repository/TextureRepository.hh"
#include "static/spdlog/spdlog.h"

TextureRepository::TextureRepository(char const &root): Repository(root) {
    // does nothihng.
}

sf::Texture *TextureRepository::create(
    char const &filename,
    char const &key
) const {
    spdlog::info("create texture: '{}'", &filename);
    sf::Texture *texture = new sf::Texture();
    if (texture->loadFromFile(&filename)) {
        texture->setSmooth(false);
        texture->setRepeated(true);
        return texture;
    }
    spdlog::error("could nto laod texture at '{}'", &filename);
    return 0;
}
