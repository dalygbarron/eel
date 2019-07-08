#include "PlainScene.hh"

void PlainScene::render(sf::RenderTarget *target, sf::RenderStates states) const {
    // TODO: this is bad, change to using a rectangleshape.
    target->clear();
}

void PlainScene::logic(long tick, char *transition) {
    // does nothing.
}

PlainScene::PlainScene(Builder const *builder, Timer *timer, Repository *repository, char const *script):
Scene(builder, timer) {
    spdlog::info("Creating plain scene with script '{}'", script);
    this->repository = repository;
    this->script = new Script(this, repository->getText(script));
    this->script->tick();
}
