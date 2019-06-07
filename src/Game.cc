#include "Game.hh"

Game::Game(Repository const *repository, char const *file) {
    this->repository = repository;
    if (ini_parse(file, handleIni, this) < 0) {
        spdlog::error("Could not open file '{}'", file);
        throw -1;
    }
}

int handleIni(void *reference, char const *section, char const *name, char const *value) {
    ((Game *)reference)->values[name] = value;
    return 1;
}
