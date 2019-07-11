#include "model/scene/PlainScene.hh"
#include <cstring>

void PlainScene::render(sf::RenderTarget *target, sf::RenderStates states) const {
    // nothing atm.
}

void PlainScene::logic(long tick) {
    if (!this->script->isAlive() && !this->transition[0]) {
        spdlog::info("Plain scene '{}' finished", this->file);
        this->transition[0] = 'r';
        this->transition[1] = 0;
    }
}

PlainScene::PlainScene(Engine const *engine, char const *filename): Scene(engine) {
    spdlog::info("Creating plain scene with script '{}'", filename);
    this->script = new Script(this, engine->repository->getText(filename));
    this->script->tick();
    this->file = new char[strlen(filename)];
    strcpy(this->file, filename);
}
