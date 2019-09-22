#include "static/Utils.hh"
#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

float Utils::min(float a, float b) {
    if (a < b) return a;
    else return b;
}

float Utils::max(float a, float b) {
    if (a > b) return a;
    else return b;
}

int Utils::isWhitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

int Utils::endOfWord(char const *string) {
    if (!string[0]) return 0;
    int i;
    for (i = 1; string[i]; i++) {
        if (Utils::isWhitespace(string[i])) return i;
    }
    return i;
}

int Utils::startOfNextWord(char const *string) {
    if (!string[0]) return 0;
    for (int i = 1; string[i]; i++) {
        if (!Utils::isWhitespace(string[i] &&
            Utils::isWhitespace(string[i - 1]))) {
            return i;
        }
    }
    return 0;
}

void Utils::fitText(char const *string, sf::FloatRect bounds, sf::Text *text) {
    char fittedContent[Constant::SMALL_TEXT_BUFFER_SIZE];
    int readHead = 0;
    int writeHead = 0;
    while (true) {
        int word = Utils::endOfWord(string + readHead);
        if (!word) break;
        if (readHead + word >= Constant::SMALL_TEXT_BUFFER_SIZE) {
            writeHead = Constant::SMALL_TEXT_BUFFER_SIZE - 1;
            spdlog::error(
                "Buffer was too small to fit whole text '{}'",
                string
            );
            break;
        }
        for (int i = 0; i < word; i++) {
            char c = string[readHead + i];
            // TODO: format strings and fancy stuff would be cool.
            //       perhaps that would belong in a different function I guess.
            if (c == '\n') fittedContent[writeHead + i] = ' ';
            else if (c == '#') fittedContent[writeHead + i] = '\n';
            else fittedContent[writeHead + i] = string[readHead + i];
        }
        text->setString(fittedContent);
        sf::FloatRect newBounds = text->getLocalBounds();
        if (newBounds.width > bounds.width) {
            readHead += Utils::startOfNextWord(string + readHead);
            fittedContent[writeHead] = '\n';
            writeHead++;
        } else if (newBounds.height > bounds.height) {
            spdlog::warn("Box was too small to fit whole text '{}'", string);
            break;
        } else {
            readHead += word;
            writeHead += word;
        }
    }
    fittedContent[writeHead] = 0;
    text->setString(fittedContent);
}

char *Utils::readFile(char const *file) {
    sf::FileInputStream input;
    if (!input.open(file)) {
        spdlog::error("Can't open file '{}' for reading", file);
        char *empty = new char[1];
        empty[0] = 0;
        return empty;
    }
    int length = input.getSize();
    char *string = new char[length + 1];
    input.read(string, length);
    string[length - 1] = 0;
    return string;
}

char *Utils::moveString(char const *string) {
    char *moved = new char[strlen(string) + 1];
    strcpy(moved, string);
    return moved;
}

sf::Vector2f Utils::wrapped(sf::Vector2f pos, sf::FloatRect bounds) {
    while (pos.x < bounds.left) pos.x += bounds.width;
    while (pos.x >= bounds.left + bounds.width) pos.x -= bounds.width;
    while (pos.y < bounds.top) pos.y += bounds.height;
    while (pos.y >= bounds.top + bounds.height) pos.y -= bounds.height;
    return pos;
}

float Utils::random() {
    return (float)rand() / RAND_MAX;
}

sf::View Utils::getLetterboxView(sf::View view, sf::Vector2i dimensions) {
    float windowRatio = dimensions.x / (float)dimensions.y;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    int horizontalSpace = true;
    if (windowRatio < viewRatio) horizontalSpace = false;
    if (horizontalSpace) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

int Utils::parseInt(char const *text) {
    return strtol(text, 0, 0);
}

void Utils::fitQuad(sf::Vertex *vertices, sf::FloatRect rect) {
    vertices[0].position = sf::Vector2f(rect.left, rect.top);
    vertices[1].position = sf::Vector2f(rect.left + rect.width, rect.top);
    vertices[2].position = sf::Vector2f(
        rect.left + rect.width,
        rect.top + rect.height
    );
    vertices[3].position = sf::Vector2f(rect.left, rect.top + rect.height);
}

void Utils::colourQuad(sf::Vertex *vertices, sf::Color colour) {
    vertices[0].color = colour;
    vertices[1].color = colour;
    vertices[2].color = colour;
    vertices[3].color = colour;
}
