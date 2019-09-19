#include "model/control/Panel.hh"
#include "model/control/TextBox.hh"
#include "model/control/Bopper.hh"
#include "static/Utils.hh"

Panel::Panel(int vertical, float border, sf::Texture *texture) {
    this->vertical = vertical;
    this->border = border;
    this->box.setOutlineThickness(border);
    this->box.setOutlineColor(sf::Color::White);
    this->box.setTexture(texture);
}

int Panel::update(unsigned char mouse) {
    for (Control *child: this->children) {
        int result = child->update(mouse);
        if (result >= 0) return result;
    }
    return -1;
}

void Panel::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->box);
    for (Control *child: this->children) child->render(target, states);
}

char const *Panel::getDescription() const {
    return "Panel";
}

sf::Vector2f Panel::getDesiredSize(sf::Vector2f bounds) const {
    return bounds;
}

sf::FloatRect Panel::resize(sf::FloatRect bounds) {
    // Panels intentionally take up all of the space given to them.
    this->dimensions = bounds;
    this->box.setPosition(sf::Vector2f(bounds.left, bounds.top));
    this->box.setSize(sf::Vector2f(bounds.width, bounds.height));
    this->box.setTextureRect(
        sf::IntRect(bounds.left, bounds.top, bounds.width, bounds.height)
    );
    // do it to the children now.
    bounds.left += this->border;
    bounds.top += this->border;
    bounds.width -= this->border * 2;
    bounds.height -= this->border * 2;
    for (Control *child: this->children) {
        sf::FloatRect childBounds = child->resize(bounds);
        if (this->vertical) {
            bounds.top += childBounds.height;
            bounds.height -= childBounds.height;
        } else {
            bounds.left += childBounds.width;
            bounds.width -= childBounds.width;
        }
    }
    return this->dimensions;
}

void Panel::addChild(Control *child) {
    this->children.push_back(child);
}
