#include "Bopper.hh"

Bopper::Bopper(sf::Color colour): vertices(sf::Triangles, 3) {
    this->colour = colour;
}

int Bopper::onEvent(sf::Event *e) {
    if (e->type == sf::Event::KeyPressed) return 0;
    else return -1;
}

void Bopper::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->vertices, states);
}

char const *Bopper::getDescription() {
    return "bopper";
}

sf::Vector2f Bopper::getDesiredSize(sf::Vector2f bounds) const {
    // TODO: should this be configurable?
    return sf::Vector2f(32, 32);
}

sf::FloatRect Bopper::resize(sf::FloatRect bounds) {
    if (bounds.width > 32) bounds.width = 32;
    if (bounds.height > 32) bounds.height = 32;
    this->vertices[0].position = sf::Vector2f(bounds.left, bounds.top);
    this->vertices[1].position = sf::Vector2f(bounds.left + bounds.width, bounds.top);
    this->vertices[2].position = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
    for (int i = 0; i < 3; i++) this->vertices[i].color = this->colour;
    return sf::FloatRect(bounds.left, bounds.top, 32, 32);
}
