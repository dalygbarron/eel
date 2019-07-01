#include "PlainScene.hh"

void PlainScene::render(sf::RenderTarget *target, sf::RenderStates states) const {
    // does nothing.
}

void PlainScene::logic() {
    // does nothing.
}

PlainScene::PlainScene(Repository *repository, char const *script): script(script) {
    this->repository = repository;
    this->script.tick();
}
