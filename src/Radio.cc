#include "Radio.hh"
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

void Radio::playSound(char const *sound, Listener *listener) {

}

void Radio::playSoundAt(char const *sound, sf::Vector3f pos, Listener *listener) {

}

void Radio::playSoundListened(char const *sound, Listener *listener) {
    for (int i = 0; i < Constant::SOUND_LISTENER_LIMIT; i++) {
        if (!this->soundListeners[i].listener) {
            sf::SoundBuffer *soundBuffer = this->repository->getSound(sound);
            if (soundBuffer) {
                this->soundListeners[i].listener = listener;
                this->soundListeners[i].
            }
        }
    }


}

void Radio::playSoundAtListened(char const *sound, sf::Vector3f pos, Listener *listener) {

}
