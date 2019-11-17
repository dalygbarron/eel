#include "model/Actor.hh"
#include <stdio.h>

void Actor::restore(Persona &proto) {
    if (!this->pane) return;
    this->pane->vertices[0].position = sf::Vector2f(0 - 64 / 2, 0 - 96 / 2);
    this->pane->vertices[1].position = sf::Vector2f(64 / 2, 0 - 96 / 2);
    this->pane->vertices[2].position = sf::Vector2f(64 / 2, 96 / 2);
    this->pane->vertices[3].position = sf::Vector2f(0 - 64 / 2, 96 / 2);
    this->pane->vertices[0].texCoords = sf::Vector2f(0, 0);
    this->pane->vertices[1].texCoords = sf::Vector2f(64, 0);
    this->pane->vertices[2].texCoords = sf::Vector2f(64, 96);
    this->pane->vertices[3].texCoords = sf::Vector2f(0, 96);
    this->alive = true;
}

void Actor::logic(float delta) {
    this->velocity.x = 0;
    this->velocity.y = 0;
    this->velocity.z = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->velocity.x = -30;
        this->velocity.y = 30;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->velocity.x = 30;
        this->velocity.y = -30;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->velocity.x = -30;
        this->velocity.y = -30;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->velocity.x = 30;
        this->velocity.y = 30;
    }
}
