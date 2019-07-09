#include "Scene.hh"
#include "Signal.hh"
#include "spdlog/spdlog.h"

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // I hate references man so I am treating this method as an adaptor to my own style.
    if (this->bg.a > 0) target.clear(this->bg);
    this->render(&target, states);
    if (this->gui) this->gui->render(&target, states);
}

Scene::Scene(Builder const *builder, Timer *timer, Radio *radio) {
    this->builder = builder;
    this->timer = timer;
    this->radio = radio;
    this->transition[0] = 0;
}

void Scene::update(long tick) {
    if (!this->gui) this->logic(tick);
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
