#include "Scene.hh"
#include "Signal.hh"
#include "spdlog/spdlog.h"

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // I hate references man so I am treating this method as an adaptor to my own style.
    this->render(&target, states);
    if (this->gui) this->gui->render(&target, states);
}

Scene::Scene(Builder const *builder, Timer *timer) {
    this->builder = builder;
    this->timer = timer;
}

void Scene::update(long tick, char *transition) {
    if (!this->gui) this->logic(tick, transition);
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
            signal.content.scene.value = response;
            delete this->gui;
            this->gui = 0;
            speak(signal);
        }
    }
}
