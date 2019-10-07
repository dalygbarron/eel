#include "service/Radio.hh"
#include "static/spdlog/spdlog.h"
#include <cstring>

Radio::Radio(SoundRepository *soundRepo, MusicRepository *musicRepo) {
    this->soundRepo = soundRepo;
    this->musicRepo = musicRepo;
}

void Radio::playSong(char const *song) {
    sf::Music *music = this->musicRepo->get(song)->content;
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

float Radio::playSound(char const *sound) {
    // TODO: this is a pretty inefficient way of doing this. Maybe I should use
    //       one of those dead lists or sometihng. also, should try to find a
    //       way of stopping the same sound from playing twice in the same
    //       frame. could store most recent name pointer and stop you from
    //       playing twice in a row in one frame. Would also need to add an
    //       update every frame though.
    for (int i = 0; i < Radio::SOUND_LIMIT; i++) {
        if (this->sounds[i].getStatus() == sf::Music::Status::Stopped) {
            sf::SoundBuffer *soundBuffer = this->soundRepo->get(sound)->content;
            this->sounds[i].setBuffer(*(soundBuffer));
            this->sounds[i].play();
            float length = soundBuffer->getDuration().asSeconds();
            spdlog::debug("Playing sound '{}' for {} seconds", sound, length);
            return length;
        }
    }
    spdlog::warn("Could not find free sound player for sound '{}'", sound);
    return 0;
}
