#include "service/repository/MusicRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Audio.hpp>

sf::Music *MusicRepository::create(char const *filename) {
    spdlog::info("creating music: '{}'", filename);
    return 0;
}
