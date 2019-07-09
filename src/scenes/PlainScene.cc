#include "PlainScene.hh"

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

PlainScene::PlainScene(Builder const *builder, Timer *timer, Radio *radio, Repository *repository, char const *script):
Scene(builder, timer, radio) {
    spdlog::info("Creating plain scene with script '{}'", script);
    this->repository = repository;
    this->script = new Script(this, repository->getText(script));
    this->script->tick();
    this->file = new char[strlen(script)];
    strcpy(this->file, script);
}
