#include "scene/SplashScene.hh"
#include "static/Utils.hh"
#include <cstring>

SplashScene::SplashScene(Engine const &engine):
    Scene(engine),
    startScript(&engine.config.getOption(*"start"))
{
    this->texture.loadFromMemory(SplashScene::LOGO, SplashScene::LOGO_SIZE);
    this->shape.setTexture(&this->texture);
    this->shape.setSize(this->engine.config.dimensions);
    this->timer = 0;
}

SplashScene::~SplashScene() {
    // nothing.
}

void SplashScene::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.draw(this->shape);
}

void SplashScene::logic(float delta) {
    this->timer += delta;
    float scale = Utils::random() / 20 + 1;
    this->shape.setScale(scale, scale);
    this->shape.setFillColor(
        sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 7)
    );
    float x = Utils::random() * this->engine.config.dimensions.x;
    float y = Utils::random() * this->engine.config.dimensions.y;
    this->shape.setOrigin(x, y);
    this->shape.setPosition(x, y);
    if (this->timer > SplashScene::WAIT) {
        this->transition[0] = 'r';
        this->transition[1] = 'p';
        strcpy(transition + 2, this->startScript.c_str());
    }
}
