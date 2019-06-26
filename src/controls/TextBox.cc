#include "TextBox.hh"
#include "../spdlog/spdlog.h"

TextBox::TextBox(char const *content) {
    // TODO: process the text a bit and copy it to a new buffer. We will only make it smaller so can have same size.
    this->content = content;

    if (!this->font.loadFromFile("example/bocklin.ttf")) {
        spdlog::error("cant open font");
        throw -1;
    }
    this->text.setFont(this->font);
    this->text.setCharacterSize(30);
    this->text.setFillColor(sf::Color::White);
    this->text.setString("It feels GOOD to kill the police man.\nIt FyEAAAY YEAAH it FEELS GOOD!");
}

void TextBox::render(sf::RenderTarget *target, sf::RenderStates states) const {
    spdlog::debug("drawing rn");
    target->draw(this->text);
    spdlog::debug("done drawing");
}

char const *TextBox::getDescription() {
    return "textbox";
}

sf::Vector2f TextBox::getDesiredSize(sf::Vector2f bounds) const {
    return bounds;
}

sf::FloatRect TextBox::resize(sf::FloatRect bounds) {
    // TODO: fit the text lines in the bounds
    this->text.setPosition(sf::Vector2f(bounds.left, bounds.top));
    return bounds;
}
