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
    // set up the border quads in a swastika formation.
    Utils::fitQuad(&this->vertices[4], sf::FloatRect(
        0,
        0,
        Panel::BORDER,
        dimensions.height - Panel::BORDER
    ));
    Utils::fitQuad(&this->vertices[8], sf::FloatRect(
        Panel::BORDER,
        0,
        dimensions.width - Panel::BORDER,
        Panel::BORDER
    ));
    Utils::fitQuad(&this->vertices[12], sf::FloatRect(
        dimensions.width - Panel::BORDER,
        Panel::BORDER,
        Panel::BORDER,
        dimensions.height - Panel::BORDER
    ));
    Utils::fitQuad(&this->vertices[16], sf::FloatRect(
        0,
        dimensions.height - Panel::BORDER,
        dimensions.width - Panel::BORDER,
        Panel::BORDER
    ));
    for (int i = 4; i < 4 + 4 * 4; i++) this->vertices[i].color = sf::Color::Red;
}

int Panel::onEvent(sf::Event *e) {
    for (Widget *child: this->children) {
        int response = child->onEvent(e);
        if (response >= 0) return response;
    }
    return -1;
}

char *Panel::getDescription() {
    return "Panel";
}
