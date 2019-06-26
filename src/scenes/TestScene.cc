#include "TestScene.hh"

#include <stdio.h>
#include "../spdlog/spdlog.h"
#include "../BulletManager.hh"
#include "../Repository.hh"
#include "../controls/Panel.hh"

void TestScene::logic() {
    this->i++;
    this->shader.setUniform("time", this->i / 60.f);
    this->shape.setTextureRect(sf::IntRect(i, this->i / -2, 200, 200));
    this->bulletManager->update();
}

void TestScene::render(sf::RenderTarget *target, sf::RenderStates states) const {
    target->draw(this->background, &this->shader);
    target->draw(this->shape);
    target->draw(*(this->bulletManager));
}

TestScene::TestScene(BulletManager *bulletManager, Config const *config, Repository *repository) {
    spdlog::info("Creating test scene");
    this->bulletManager = bulletManager;
    if (!this->texture.loadFromFile("example/image/bg.png")) {
        spdlog::error("Couldn't load font or stuff for test scene");
        throw -1;
    }
    this->texture.setRepeated(true);
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
    this->shape.setSize(sf::Vector2f(640, 480));
    this->shape.setPosition(500, 500);
    this->text.setFont(*(repository->getFont()));
    this->text.setString("Eel game");
    this->text.setCharacterSize(40);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(0, 0);
    this->background.setSize(sf::Vector2f(1280, 960));
    this->background.setPosition(0, 0);
    this->background.setTextureRect(sf::IntRect(0, 0, 1, 1));
    if (!this->shader.loadFromFile("example/shader/plain.vert", "example/shader/bullet.frag")) {
        spdlog::error("Couldn't load nice shaders for test scene");
        throw -1;
    }
    this->shader.setUniform("resolution", sf::Vector2f(1280, 960));
    // TODO: clear the bullet manager before use.
    for (int i = 0; i < Constant::BULLET_LIMIT; i += 3) {
        this->bulletManager->addBullet(this->bulletManager->getPrototype("roe"), sf::Vector2f(rand() % 1280, rand() % 900));
        this->bulletManager->addBullet(this->bulletManager->getPrototype("bubble"), sf::Vector2f(rand() % 1280, rand() % 900));
        this->bulletManager->addBullet(this->bulletManager->getPrototype("dispenser"), sf::Vector2f(rand() % 1280, rand() % 900));
    }
    Control *panel = new Panel(true, 4.3, sf::Color::White, sf::Color(0, 0, 30, 220));
    panel->resize(sf::FloatRect(100, 100, 640, 222));
    addControl(panel);
}
