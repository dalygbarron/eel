#include "TestScene.hh"

#include "spdlog/spdlog.h"

void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, &shader);
    target.draw(shape);
    target.draw(text);
}


TestScene::TestScene() {
    if (!font.loadFromFile("test/font/bocklin.ttf") || !texture.loadFromFile("test/image/bg.png")) {
        spdlog::error("Couldn't load font or stuff for test scene");
        throw -1;
    }
    texture.setRepeated(true);
    texture.setSmooth(true);
    sf::RectangleShape shape(sf::Vector2f(640, 480));
    shape.setTexture(&texture);
    shape.setPosition(500, 500);
    sf::Text text;
    text.setFont(font);
    text.setString("League of Piss");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    sf::RectangleShape background(sf::Vector2f(960, 1440));
    background.setPosition(0, 0);
    background.setTextureRect(sf::IntRect(0, 0, 1, 1));
    sf::Shader shader;
    if (!shader.loadFromFile("test/shader/plain.vert", "test/shader/plain.frag")) {
        spdlog::error("Couldn't load nice shaders for test scene");
        throw -1;
    }
    shader.setUniform("resolution", sf::Vector2f(WIDTH, HEIGHT));
}

void TestScene::update(Transition *transition) {
    shader.setUniform("time", i / 60.f);
    shape.setTextureRect(sf::IntRect(i, i / -2, 200, 200));
}
