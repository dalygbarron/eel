#include "scene/PlainScene.hh"
#include <cstring>

PlainScene::PlainScene(
    Engine const &engine,
    char const &filename
):
    Scene(engine),
    script(*this, engine.getTextRepository().get(filename).get())
{
    spdlog::info("Creating plain scene with script '{}'", filename);
    // TODO: maybe script object itself should be cached.
    //       dunno if that is possible / worthwhile tbh.
}

PlainScene::~PlainScene() {
    // does nothing atm.
}
void PlainScene::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    // nothing atm.
}

void PlainScene::logic(float delta) {
    if (this->script.isAlive()) {
        this->script.tick(delta);
    } else if (!this->transition[0]) {
        this->transition[0] = 'r';
        this->transition[1] = 0;
    }
}


