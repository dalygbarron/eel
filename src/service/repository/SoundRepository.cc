#include "service/repository/SoundRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"

SoundRepository::SoundRepository(char const &root): Repository(root) {
    // Does nothing.
}

sf::SoundBuffer *SoundRepository::create(
    char const &filename,
    char const &key
) const {
    spdlog::info("creating sound: '{}'", filename);
    sf::SoundBuffer &sound = new sf::SoundBuffer();
    if (sound.loadFromFile(filename)) {
        return sound;
    }
    spdlog::error("Cannot load sound at '{}'", filename);
    return 0;
}
