#include "service/repository/MusicRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Audio.hpp>

MusicRepository::MusicRepository(char const *root): Repository(root) {
    // nothing here.
}

sf::Music *MusicRepository::create(char const *filename, char const *key) {
    spdlog::info("creating music: '{}'", filename);
    return 0;
}
