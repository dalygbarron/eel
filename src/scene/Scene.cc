#include "scene/Scene.hh"
#include "model/Signal.hh"
#include "static/spdlog/spdlog.h"

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (this->bg.a > 0) target.clear(this->bg);
    this->render(&target, states);
    if (this->gui) this->gui->render(&target, states);
}

Scene::Scene(Engine const *engine) {
    this->engine = engine;
    this->transition[0] = 0;
}

Scene::~Scene() {
    // Does nothing I think.
}

void Scene::update(float delta, unsigned char mouse) {
    if (!this->gui) this->logic(delta);
}

void Scene::addControl(Control *control) {
    this->gui = control;
}
