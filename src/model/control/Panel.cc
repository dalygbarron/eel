#include "model/control/Panel.hh"
#include "model/control/TextBox.hh"
#include "model/control/Bopper.hh"
#include "static/Utils.hh"

Panel::Panel(): vertices(sf::Quads) {
    // does nothing.
}

Panel::Panel(
    int vertical,
    float border,
    int borderMode,
    sf::Color fg,
    sf::Color bg
): vertices(sf::Quads) {
    this->vertical = vertical;
    this->border = border;
    this->borderMode = borderMode;
    this->fg = fg;
    this->bg = bg;
}

int Panel::update(unsigned char mouse) {
    for (Control *child: this->children) {
        int result = child->update(mouse);
        if (result >= 0) return result;
    }
    return -1;
}

void Panel::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->vertices);
    for (Control *child: this->children) child->render(target, states);
}

char const *Panel::getDescription() const {
    return "Panel";
}

sf::Vector2f Panel::getDesiredSize(sf::Vector2f bounds) const {
    return bounds;
}

sf::FloatRect Panel::resize(sf::FloatRect bounds) {
    this->vertices.resize(12);
    // Panels intentionally take up all of the space given to them.
    this->dimensions = bounds;
    if (this->borderMode == Panel::BORDER_VERTICAL) {
        Utils::makeStack(
            &this->vertices[0],
            bounds,
            this->border,
            this->fg,
            this->bg
        );
    } else if (this->borderMode == Panel::BORDER_HORIZONTAL) {
        Utils::makeWall(
            &this->vertices[0],
            bounds,
            this->border,
            this->fg,
            this->bg
        );
    } else {
        spdlog::error("No such panel border mode as {}", this->borderMode);
    }
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
