#include "Widget.hh"

Widget::Widget(sf::FloatRect dimensions) {
    this->dimensions = dimensions;
}

int Widget::onEvent(sf::Event *event) {
    return 0;
}
