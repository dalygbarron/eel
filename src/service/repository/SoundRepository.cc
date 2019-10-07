#include "service/repository/SoundRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"

sf::SoundBuffer *SoundRepository::create(char const *filename) {
    spdlog::info("creating sound: '{}'", filename);
    sf::SoundBuffer *sound = new sf::SoundBuffer();
    if (sound->loadFromFile(filename)) {
        return sound;
    }
    spdlog::error("Cannot load sound at '{}'", filename);
    return 0;
}
