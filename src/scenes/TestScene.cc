#include "TestScene.hh"

#include <stdio.h>
#include "../spdlog/spdlog.h"

void TestScene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->background, &this->shader);
    target.draw(this->shape);
    target.draw(this->text);
}

TestScene::TestScene() {
    spdlog::info("Creating test scene");
    if (!this->font.loadFromFile("test/font/bocklin.ttf") || !this->texture.loadFromFile("test/image/bg.png")) {
        spdlog::error("Couldn't load font or stuff for test scene");
        throw -1;
    }
    this->texture.setRepeated(true);
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
    this->shape.setSize(sf::Vector2f(640, 480));
    this->shape.setPosition(500, 500);
    this->text.setFont(font);
    this->text.setString("League of Piss");
    this->text.setCharacterSize(40);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(0, 0);
    this->background.setSize(sf::Vector2f(960, 1440));
    this->background.setPosition(0, 0);
    this->background.setTextureRect(sf::IntRect(0, 0, 1, 1));
    if (!this->shader.loadFromFile("test/shader/plain.vert", "test/shader/plain.frag")) {
        spdlog::error("Couldn't load nice shaders for test scene");
        throw -1;
    }
    this->shader.setUniform("resolution", sf::Vector2f(1440, 960));
}

void TestScene::update(Transition *transition) {
    this->i++;
    this->shader.setUniform("time", this->i / 60.f);
    this->shape.setTextureRect(sf::IntRect(i, this->i / -2, 200, 200));
}
