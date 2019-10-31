#include "scene/PlainScene.hh"
#include <cstring>

PlainScene::PlainScene(
    Engine const *engine,
    char const *filename
): Scene(engine) {
    spdlog::info("Creating plain scene with script '{}'", filename);
    // TODO: maybe script object itself should be cached.
    //       dunno if that is possible / worthwhile tbh.
    this->script = new Script(
        this,
        engine->getTextRepository()->get(filename)->get()
    );
    this->file = new char[strlen(filename) + 1];
    strcpy(this->file, filename);
}

PlainScene::~PlainScene() {
    delete this->file;
    delete this->script;
}
void PlainScene::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    // nothing atm.
}

void PlainScene::logic(float delta) {
    if (this->script->isAlive()) {
        this->script->tick(delta);
    } else if (!this->transition[0]) {
        spdlog::info("Plain scene '{}' finished", this->file);
        this->transition[0] = 'r';
        this->transition[1] = 0;
    }
}


