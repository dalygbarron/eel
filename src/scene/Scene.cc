#include "scene/Scene.hh"
#include "static/spdlog/spdlog.h"

Scene::Scene(Engine const *engine) {
    this->engine = engine;
    this->transition[0] = 0;
}

Scene::~Scene() {
    // Does nothing I think.
}

void Scene::update(float delta, unsigned char mouse) {
    if (this->gui) {
        this->result = this->gui->update(mouse);
        if (this->result >= 0) {
            delete this->gui;
            this->gui = 0;
        }
    } else {
        this->logic(delta);
    }
}

void Scene::addControl(Control *control) {
    this->gui = control;
}

int Scene::getResult() const {
    return this->result;
}
