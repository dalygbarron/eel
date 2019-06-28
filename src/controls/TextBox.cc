#include "TextBox.hh"
#include "../Constant.hh"
#include "../Utils.hh"
#include "../spdlog/spdlog.h"
#include <stdio.h>

void TextBox::fitContent(sf::FloatRect bounds) {
    // TODO: refactor this to keep the string manipulation but keep the sizing stuff elsewhere.
    //       maybe even move this to utils just as a fitting text into a box kinda deal.
    char fittedContent[Constant::SMALL_TEXT_BUFFER_SIZE];
    char *endOfWord = fittedContent;
    char const *readHead = this->content;
    char *writeHead = fittedContent;
    for (int i = 0; this->content[i]; i++) {
        if (Utils::isWhitespace(this->content[i])) {
            endOfWord = fittedContent + (readHead - this->content);
        } else {
            if (readHead - endOfWord > 1) {
                *writeHead = this->content[i];
                writeHead++;
                *writeHead = 0;
                this->text.setString(fittedContent);
                sf::FloatRect textBounds = this->text.getLocalBounds();
                if (textBounds.width > bounds.width) {
                    endOfWord[1] = '\n';
                    for (int v = endOfWord - fittedContent + 2; v < fittedContent - writeHead; v++) {
                        fittedContent[v] = this->content[v];
                    }
                }
                if (textBounds.height > bounds.height) {
                    endOfWord[1] = 0;
                    this->text.setString(fittedContent);
                    return;
                }
            }
            readHead = this->content + i;
        }
        *writeHead = this->content[i];
        writeHead++;
    }
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
