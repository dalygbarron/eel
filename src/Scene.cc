#include "Scene.hh"
#include "spdlog/spdlog.h"

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    this->render(target, states);
    if (this->gui) target.draw(*(this->gui));
}


Scene::Scene() {
    // does nothing rn.
}

void Scene::update() {
    if (this->gui) {
        // TODO: don't think we need to do this I dunno.
        //       gui elements don't update frame by frame, they respond to events.
    } else {
        this->logic();
    }
}

void Scene::addControl(Control *widget) {
    this->gui = widget;
}

void Scene::onEvent(sf::Event *event) {
    if (this->gui) this->gui->onEvent(event);
}
