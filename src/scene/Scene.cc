#include "scene/Scene.hh"
#include "static/spdlog/spdlog.h"

Scene::Scene(Engine const &engine): engine(engine) {
    this->transition[0] = 0;
}

Scene::~Scene() {
    // Does nothing I think.
}

void Scene::update(float delta, unsigned char mouse, sf::View &view) {
    if (this->gui) {
        this->result = this->gui->update(mouse);
        if (this->result >= 0) {
            delete this->gui;
            this->gui = 0;
        }
    } else {
        this->logic(delta, view);
    }
}

void Scene::addControl(Control &control) {
    this->gui = &control;
}

int Scene::getResult() const {
    return this->result;
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (this->bg.a > 0) target.clear(this->bg);
    if (this->gui) target.draw(*this->gui);
}
