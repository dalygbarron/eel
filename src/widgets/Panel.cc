#include "Panel.hh"
#include "../Config.hh"
#include "../Utils.hh"

void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

Panel::Panel(sf::FloatRect dimensions, Config *config): Widget(dimensions), vertices(sf::Quads, 20) {
    // set up the middle part
    Utils::fitQuad(&this->vertices[0], sf::FloatRect(
        dimensions.left + Panel::BORDER,
        dimensions.top + Panel::BORDER,
        dimensions.left + dimensions.width - Panel::BORDER,
        dimensions.top + dimensions.height - Panel::BORDER
    ));
    Utils::colourQuad(&this->vertices[0], sf::Color::Green);
    // set up the border parts
    this->vertices[5].position = sf::Vector2f(dimensions.left + Panel::BORDER, dimensions.top + Panel::BORDER);
}

int Panel::onEvent(sf::Event *e) {
    for (Widget *child: this->children) {

    }

}
