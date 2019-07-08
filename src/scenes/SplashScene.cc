#include "SplashScene.hh"
#include <cstring>

void SplashScene::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->shape);
}

void SplashScene::logic(long tick, char *transition) {
    // does nothing.
    float scale = Utils::random() / 20 + 1;
    this->shape.setScale(scale, scale);
    this->shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 40));
    float x = Utils::random() * this->width;
    float y = Utils::random() * this->height;
    this->shape.setOrigin(x, y);
    this->shape.setPosition(x, y);
    if (tick == SplashScene::WAIT) {
        transition[0] = 'r';
        transition[1] = 'p';
        strcpy(transition + 2, this->startScript);
    }
}

SplashScene::SplashScene(Builder const *builder, Timer *timer, Config const *config): Scene(builder, timer) {
    this->texture.loadFromMemory(SplashScene::LOGO, SplashScene::LOGO_SIZE);
    this->shape.setTexture(&(this->texture));
    this->width = Utils::parseInt(config->get("width"));
    this->height = Utils::parseInt(config->get("height"));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->startScript = config->get("start");
}
