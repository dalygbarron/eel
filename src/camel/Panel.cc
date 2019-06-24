#include "Panel.hh"
#include "../Config.hh"
#include "../Utils.hh"

void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->vertices);
    for (Widget *child: this->children) target.draw(*child);
}

Panel::Panel(Config const *config, int vertical): vertices(sf::Quads, 20) {
    this->vertical = vertical;
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

sf::Vector2f Panel::getDesiredSize() {

}

sf::FloatRect Panel::resize(sf::FloatRect bounds) {
    // Panels intentionally take up all of the space given to them.
    this->dimensions = bounds;
    // TODO: load colours from game file and save in config object.
    Utils::makeBox(&this->vertices[0], bounds, Panel::BORDER, sf::Color::Blue, sf::Color::White);
    // do it to the children now.
    bounds.left += Panel::BORDER;
    bounds.top += Panel::BORDER;
    bounds.width -= Panel::BORDER * 2;
    bounds.height -= Panel::BORDER * 2;
    for (Widget *child: this->children) {
        sf::FloatRect childBounds = child->resize(bounds);
        if (this->vertical) {
            bounds.top = childBounds.top + childBounds.height;
            bounds.height -= childBounds.height;
        } else {
            bounds.left = childBounds.left + childBounds.width;
            bounds.width -= childBounds.width;
        }
    }
    return this->dimensions;
}
