#include "Game.hh"
#include <string>
#include "spdlog/spdlog.h"
#include "inih.hh"

Game::Game(char const *file): Store(file) {
    spdlog::info("Loading game data from '{}'", file);
    // Load in flags.
    if (ini_parse(file, Game::handleIni, this) < 0) {
        spdlog::error("Could not open file '{}'", file);
        throw -1;
    }
    // Save root directory where file was.
    int directory = -1;
    for (int i = 0; file[i]; i++) {
        if (file[i] == '/') directory = i;
    }
    this->root = new char[directory + 1];
    memcpy(this->root, file, directory);
    this->root[directory] = 0;
    spdlog::info("game root is '{}'", this->root);
}

Game::~Game() {
    delete this->root;
}

char const *Game::getRoot() const {
    return this->root;
}

int Game::inRoot(char *buffer, char const *file) const {
    return sprintf(buffer, "%s/%s", this->root, file);
}

int Game::handleIni(void *reference, char const *section, char const *name, char const *value) {
    spdlog::debug("game value '{}': '{}'", name, value);
    char *newValue = new char[strlen(value)];
    strcpy(newValue, value);
    Game *game = (Game *)reference;
    game->values[name] = newValue;
    return 1;
}
