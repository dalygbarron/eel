#include "Utils.hh"
#include "Config.hh"
#include <SFML/Graphics.hpp>

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
    return value / Config::FPS;
}

float Utils::perSecondPerSecond(float value) {
    return value / (Config::FPS * Config::FPS);
}

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {
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
