#include "Panel.hh"
#include "../Utils.hh"

Panel::Panel(int vertical, float border, sf::Color fg, sf::Color bg): vertices(sf::Quads, 12) {
    this->vertical = vertical;
    this->border = border;
    this->fg = fg;
    this->bg = bg;
}

int Panel::onEvent(sf::Event *e) {
    for (Control *child: this->children) {
        int response = child->onEvent(e);
        if (response >= 0) return response;
    }
    return -1;
}

void Panel::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->vertices);
    for (Control *child: this->children) child->render(target, states);
}

char const *Panel::getDescription() {
    return "Panel";
}

sf::Vector2f Panel::getDesiredSize(sf::Vector2f bounds) {
    return bounds;
}

sf::FloatRect Panel::resize(sf::FloatRect bounds) {
    // Panels intentionally take up all of the space given to them.
    this->dimensions = bounds;
    // TODO: load colours from game file and save in config object.
    Utils::makeStack(&this->vertices[0], bounds, this->border, this->fg, this->bg);
    // do it to the children now.
    bounds.left += this->border;
    bounds.top += this->border;
    bounds.width -= this->border * 2;
    bounds.height -= this->border * 2;
    for (Control *child: this->children) {
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

void Panel::addChild(Control *child) {
    this->children.push_front(child);
}
