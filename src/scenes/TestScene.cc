#include "TestScene.hh"

#include <stdio.h>
#include "../spdlog/spdlog.h"
#include "../BulletManager.hh"
#include "../Repository.hh"
#include "../controls/Panel.hh"

void TestScene::logic() {
    this->i++;
    this->shader.setUniform("time", this->i / 60.f);
    this->bulletManager->update();
}

void TestScene::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->background, &this->shader);
    target->draw(*(this->bulletManager));
    this->leftPanel.render(target, states);
    this->rightPanel.render(target, states);
}

TestScene::TestScene(
    Builder const *builder,
    Timer *timer,
    BulletManager *bulletManager,
    Config const *config,
    Repository *repository
): Scene(builder, timer) {
    spdlog::info("Creating test scene");
    this->bulletManager = bulletManager;
    this->background.setSize(sf::Vector2f(640, 960));
    this->background.setPosition(320, 0);
    this->background.setTextureRect(sf::IntRect(0, 0, 1, 1));
    if (!this->shader.loadFromFile("example/shader/plain.vert", "example/shader/bullet.frag")) {
        spdlog::error("Couldn't load nice shaders for test scene");
        throw -1;
    }
    this->shader.setUniform("resolution", sf::Vector2f(1280, 960));
    // TODO: clear the bullet manager before use.
    for (int i = 0; i < Constant::BULLET_LIMIT; i += 20) {
        this->bulletManager->addBullet(this->bulletManager->getPrototype("roe"), sf::Vector2f(320 + rand() % 640, rand() % 900));
        this->bulletManager->addBullet(this->bulletManager->getPrototype("bubble"), sf::Vector2f(320 + rand() % 640, rand() % 900));
        this->bulletManager->addBullet(this->bulletManager->getPrototype("dispenser"), sf::Vector2f(320 + rand() % 640, rand() % 900));
    }
    this->leftPanel.vertical = true;
    this->leftPanel.border = 4.3;
    this->leftPanel.borderMode = Panel::BORDER_HORIZONTAL;
    this->leftPanel.fg = sf::Color::White;
    this->leftPanel.bg = sf::Color(0, 0, 20);
    this->leftPanel.resize(sf::FloatRect(0, 0, 320, 960));
    this->rightPanel.vertical = true;
    this->rightPanel.border = 4.3;
    this->rightPanel.borderMode = Panel::BORDER_HORIZONTAL;
    this->rightPanel.fg = sf::Color::White;
    this->rightPanel.bg = sf::Color(0, 0, 20);
    this->rightPanel.resize(sf::FloatRect(960, 0, 320, 960));
    // load in the script
}
