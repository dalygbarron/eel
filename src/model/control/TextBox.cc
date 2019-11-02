#include "model/control/TextBox.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <stdio.h>

TextBox::TextBox(char const &content, float size): content(content) {
    // TODO: drop this shit.
    if (!this->font.loadFromFile("example/bocklin.ttf")) {
        spdlog::critical("cant open font");
        throw new std::runtime_error("can't open font");
    }
    this->text.setFont(this->font);
    this->text.setCharacterSize(size);
    this->text.setFillColor(sf::Color::White);
}

char const &TextBox::getDescription() const {
    return *"textbox";
}

sf::Vector2f TextBox::getDesiredSize(sf::Vector2f bounds) const {
    return bounds;
}

sf::FloatRect TextBox::resize(sf::FloatRect bounds) {
    Utils::fitText(this->content, bounds, this->text);
    sf::FloatRect localBounds = this->text.getLocalBounds();
    this->text.setPosition(sf::Vector2f(
        bounds.left,
        bounds.top - localBounds.top
    ));
    sf::Vector2f pos = this->text.getPosition();
    return this->text.getLocalBounds();
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->text);
}
