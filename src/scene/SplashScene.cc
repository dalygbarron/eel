#include "scene/SplashScene.hh"
#include <cstring>

SplashScene::SplashScene(Engine const *engine): Scene(engine) {
    this->texture.loadFromMemory(SplashScene::LOGO, SplashScene::LOGO_SIZE);
    this->shape.setTexture(&(this->texture));
    this->width = Utils::parseInt(engine->config->get("width"));
    this->height = Utils::parseInt(engine->config->get("height"));
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->startScript = engine->config->get("start");
    this->timer = 0;
}

SplashScene::~SplashScene() {
    // TODO: delete the splash picture.
}

void SplashScene::render(
    sf::RenderTarget *target,
    sf::RenderStates states
) const {
    target->draw(this->shape);
}

void SplashScene::logic(float delta) {
    this->timer += delta;
    float scale = Utils::random() / 20 + 1;
    this->shape.setScale(scale, scale);
    this->shape.setFillColor(
        sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 40)
    );
    float x = Utils::random() * this->width;
    float y = Utils::random() * this->height;
    this->shape.setOrigin(x, y);
    this->shape.setPosition(x, y);
    if (this->timer > SplashScene::WAIT) {
        this->transition[0] = 'r';
        this->transition[1] = 'p';
        strcpy(transition + 2, this->startScript);
    }
}
