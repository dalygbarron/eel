#include "Scene.hh"
#include "spdlog/spdlog.h"

void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    this->drawContent(target, states);
    for (std::list<Widget >::const_iterator it = this->widgets.end(); it != this->widgets.end(); --it) {
        target->render(widget);
    }
}


Scene::Scene() {
    // does nothing rn.
}


void Scene::addWidget(Widget *widget) {
    this->widgets.push_front(widget);
}
