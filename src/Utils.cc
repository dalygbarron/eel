#include "Utils.hh"
#include "Config.hh"
#include "Constant.hh"
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

float Utils::perSecond(float value) {
    return value / Constant::FPS;
}

float Utils::perSecondPerSecond(float value) {
    return value / (Constant::FPS * Constant::FPS);
}

sf::View Utils::getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
    float windowRatio = windowWidth / (float)windowHeight;
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
    vertices[2].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    vertices[3].position = sf::Vector2f(rect.left, rect.top + rect.height);
}

void Utils::colourQuad(sf::Vertex *vertices, sf::Color colour) {
    vertices[0].color = colour;
    vertices[1].color = colour;
    vertices[2].color = colour;
    vertices[3].color = colour;
}

void Utils::makeBox(sf::Vertex *vertices, sf::FloatRect dimensions, float border, sf::Color fg, sf::Color bg) {
    // set up the middle part.
    Utils::fitQuad(vertices, sf::FloatRect(
        dimensions.left + border,
        dimensions.top + border,
        dimensions.width - border,
        dimensions.height - border
    ));
    // set up the border quads in a swastika formation.
    Utils::fitQuad(vertices + 4, sf::FloatRect(
        dimensions.left,
        dimensions.top,
        border,
        dimensions.height - border
    ));
    Utils::fitQuad(vertices + 8, sf::FloatRect(
        dimensions.left + border,
        dimensions.top,
        dimensions.width - border,
        border
    ));
    Utils::fitQuad(vertices + 12, sf::FloatRect(
        dimensions.left + dimensions.width - border,
        dimensions.top + border,
        border,
        dimensions.height - border
    ));
    Utils::fitQuad(vertices + 16, sf::FloatRect(
        dimensions.left,
        dimensions.top + dimensions.height - border,
        dimensions.width - border,
        border
    ));
    // Colouring.
    for (int i = 0; i < 4; i++) vertices[i].color = bg;
    for (int i = 4; i < 4 + 4 * 4; i++) vertices[i].color = fg;
}

void Utils::makeStack(sf::Vertex *vertices, sf::FloatRect dimensions, float border, sf::Color fg, sf::Color bg) {
    // Middle part.
    Utils::fitQuad(vertices, sf::FloatRect(
        dimensions.left,
        dimensions.top + border,
        dimensions.width,
        dimensions.height - border * 2
    ));
    // Top and bottom.
    Utils::fitQuad(vertices + 4, sf::FloatRect(
        dimensions.left,
        dimensions.top,
        dimensions.width,
        border
    ));
    Utils::fitQuad(vertices + 8, sf::FloatRect(
        dimensions.left,
        dimensions.top + dimensions.height - border,
        dimensions.width,
        border
    ));
    // Colouring.
    for (int i = 0; i < 4; i++) vertices[i].color = bg;
    for (int i = 4; i < 4 + 2 * 4; i++) vertices[i].color = fg;
}
