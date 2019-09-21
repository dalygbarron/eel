#include "model/control/Button.hh"

Button::Button(int id, Control *content) {
    this->id = id;
    this->content = content;
}

Button::~Button() {
    delete this->content;
}

int Button::update(unsigned char mouse) {
    // TODO: get position of mouse and check if it is inside this object, then 
    // either trigger if mouse is clicked, or just change the colour of the
    // quads that we render to make it highlighted.
}

void Button::render(sf::RenderTarget *target, sf::RenderStates states) const {
    // TODO: display quads.
}

char const *Button::getDescription() const {
    return "button";
}

sf::FloatRect Button::resize(sf::FloatRect bounds) {
    // TODO: actually this is where we make those quads, not up there.
}
