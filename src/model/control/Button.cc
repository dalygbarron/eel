#include "src/model/control/Button.hh"

Button::Button(int id, Control *content): vertices(sf::Quads) {
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

char const *getDescription() const {
    return "button";
}

sf::FloatRect resize(sf::FloatRect bounds) {
    // TODO: actually this is where we make those quads, not up there.
}
