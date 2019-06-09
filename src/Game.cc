#include "Game.hh"
#include "spdlog/spdlog.h"
#include "inih.hh"

Game::Game(Repository const *repository, char const *file): Store(file) {
    spdlog::info("Loading game data from '{}'", file);
    this->repository = repository;
    if (ini_parse(file, Game::handleIni, this) < 0) {
        spdlog::error("Could not open file '{}'", file);
        throw -1;
    }
}

char const *Game::getRoot() {

}

char const *Game::inRoot(char const *file) {

}

int Game::handleIni(void *reference, char const *section, char const *name, char const *value) {
    spdlog::debug("game value '{}': '{}'", name, value);
    char *newValue = new char[strlen(value)];
    strcpy(newValue, value);
    Game *game = (Game *)reference;
    game->values[name] = newValue;
    return 1;
}
