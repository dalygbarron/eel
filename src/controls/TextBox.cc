#include "TextBox.hh"
#include "../Constant.hh"
#include "../Utils.hh"
#include "../spdlog/spdlog.h"
#include <stdio.h>

void TextBox::fitContent(sf::FloatRect bounds) {
    // TODO: refactor this to keep the string manipulation but keep the sizing stuff elsewhere.
    //       maybe even move this to utils just as a fitting text into a box kinda deal.
    char fittedContent[Constant::SMALL_TEXT_BUFFER_SIZE];
    int readHead = 0;
    int writeHead = 0;
    while (true) {
        int word = Utils::endOfWord(this->content + readHead);
        if (!word) break;
        for (int i = 0; i < word; i++) {
            char c = this->content[readHead + i];
            if (c == '\n') fittedContent[writeHead + i] = ' ';
            else if (c == '#') fittedContent[writeHead + i] = '\n';
            else fittedContent[writeHead + i] = this->content[readHead + i];
        }
        this->text.setString(fittedContent);
        sf::FloatRect newBounds = this->text.getLocalBounds();
        if (newBounds.width > bounds.width) {
            readHead += Utils::startOfNextWord(this->content + readHead);
            fittedContent[writeHead] = '\n';
            writeHead++;
        } else {
            readHead += word;
            writeHead += word;
        }
    }
    fittedContent[writeHead] = 0;

    this->text.setString(fittedContent);
}

TextBox::TextBox(char const *content, float size) {
    this->content = content;
    // TODO: drop this shit.
    if (!this->font.loadFromFile("example/bocklin.ttf")) {
        spdlog::error("cant open font");
        throw -1;
    }
    this->text.setFont(this->font);
    this->text.setCharacterSize(size);
    this->text.setFillColor(sf::Color::White);
}

void TextBox::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->text);
}

char const *TextBox::getDescription() {
    return "textbox";
}

sf::Vector2f TextBox::getDesiredSize(sf::Vector2f bounds) const {
    return bounds;
}

sf::FloatRect TextBox::resize(sf::FloatRect bounds) {
    this->text.setPosition(sf::Vector2f(bounds.left, bounds.top));
    this->fitContent(bounds);
    return this->text.getLocalBounds();
}
