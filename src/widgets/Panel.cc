#include "Panel.hh"
#include "../Config.hh"
#include "../Utils.hh"

void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->vertices);
}

Panel::Panel(sf::FloatRect dimensions, Config const *config): Widget(dimensions), vertices(sf::Quads, 20) {
    // TODO: load colours from game file and save in config object.
    Utils::makeBox(&this->vertices[0], dimensions, Panel::BORDER, sf::Color::Blue, sf::Color::White);
}

int Panel::onEvent(sf::Event *e) {
    for (Widget *child: this->children) {
        int response = child->onEvent(e);
        if (response >= 0) return response;
    }
    return -1;
}

char const *Panel::getDescription() {
    return "Panel";
}
