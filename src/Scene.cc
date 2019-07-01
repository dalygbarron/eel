#include "Scene.hh"
#include "spdlog/spdlog.h"

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // I hate references man so I am treating this method as an adaptor to my own style.
    this->render(&target, states);
    if (this->gui) this->gui->render(&target, states);
}

Scene::Scene() {
    // does nothing rn.
}

void Scene::update() {
    if (!this->gui) this->logic();
}

void Scene::addControl(Control *control) {
    this->gui = control;
}

void Scene::onEvent(sf::Event *event) {
    if (this->gui) {
        int response = this->gui->onEvent(event);
        if (response >= 0) {
            // TODO: put event text in that log message.
            spdlog::debug("Control '{}' responded to event 'TODO' with {}", this->gui->getDescription(), response);
            Signal signal;
            signal.type = Signal::TYPE_SCENE;
            signal.value = response;
            speak(signal);
            delete this->gui;
            this->gui = 0;
        }
    }
}
