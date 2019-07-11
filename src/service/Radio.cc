#include "service/Radio.hh"
#include <cstring>

Radio::Radio(Repository *repository) {
    this->repository = repository;
}

void Radio::playSong(char const *song) {
    sf::Music *music = this->repository->getSong(song);
    if (!music) {
        spdlog::error("Cannot find song '{}'", song);
        return;
    }
    if (music == this->currentSong) {
        spdlog::debug("Not playing '{}' as it's already playing", song);
        return;
    }
    if (this->currentSong) this->currentSong->stop();
    music->play();
    this->currentSong = music;
}

void Radio::stopSong() {
    if (this->currentSong) this->currentSong->stop();
    this->currentSong = 0;
}

int Radio::playSound(char const *sound) {
    // TODO: this is a pretty inefficient way of doing this. Maybe I should use one of those dead lists or sometihng.
    //       also, should try to find a way of stopping the same sound from playing twice in the same frame.
    //       could store most recent name pointer and stop you from playing twice in a row in one frame. Would also need
    //       to add an update every frame though.
    for (int i = 0; i < Constant::SOUND_LIMIT; i++) {
        if (this->sounds[i].getStatus() == sf::Music::Status::Stopped) {
            sf::SoundBuffer *soundBuffer = this->repository->getSound(sound);
            this->sounds[i].setBuffer(*(soundBuffer));
            this->sounds[i].play();
            int length = ceil(soundBuffer->getDuration().asSeconds() * Constant::FPS);
            spdlog::debug("Playing sound '{}' for {} frames", sound, length);
            return length;
        }
    }
    spdlog::warn("Could not find free sound player for sound '{}'", sound);
}

int Radio::playSoundAt(char const *sound, sf::Vector3f pos) {
    // TODO: make this positioned.
    for (int i = 0; i < Constant::SOUND_LIMIT; i++) {
        if (this->sounds[i].getStatus() == sf::Music::Status::Stopped) {
            sf::SoundBuffer *soundBuffer = this->repository->getSound(sound);
            this->sounds[i].setBuffer(*(soundBuffer));
            this->sounds[i].play();
            return ceil(soundBuffer->getDuration().asSeconds() / Constant::FPS);
        }
    }
    spdlog::warn("Could not find free sound player for sound '{}'", sound);

}
