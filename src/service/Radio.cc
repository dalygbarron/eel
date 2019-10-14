#include "service/Radio.hh"
#include "static/spdlog/spdlog.h"
#include <cstring>

Radio::Radio(SoundRepository *soundRepo) {
    this->soundRepo = soundRepo;
    this->songName[0] = 0;
}

void Radio::playSong(char const *song) {
    if (strcmp(this->songName, song) == 0) {
        spdlog::debug("Not changing song as it's same");
        return;
    }
    if (this->music.openFromFile(song)) {
        strncpy(this->songName, song, Constant::FILENAME_BUFFER_SIZE);
        this->music.play();
    } else {
        this->songName[0] = 0;
        this->music.stop();
    }
}

void Radio::stopSong() {
    if (this->songName[0]) this->music.stop();
    this->songName[0] = 0;
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
            sf::SoundBuffer const *soundBuffer = this->soundRepo->get(sound)->get();
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
