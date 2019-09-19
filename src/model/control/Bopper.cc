#include "model/control/Bopper.hh"

int Bopper::update(unsigned char mouse) {
    if (mouse) return 0;
    return -1;
}

void Bopper::render(sf::RenderTarget *target, sf::RenderStates states) const {
    // doesn't do anything.
}

char const *Bopper::getDescription() const {
    return "bopperingobongo";
}

sf::Vector2f Bopper::getDesiredSize(sf::Vector2f bounds) const {
    return sf::Vector2f(0, 0);
}

sf::FloatRect Bopper::resize(sf::FloatRect bounds) {
    return sf::FloatRect(0, 0, 0, 0);
}
