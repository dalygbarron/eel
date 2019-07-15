#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>

/**
 * Represents a general dude who can participate in a bullet hell scene and maybe other scenes too.
 * They are only for moving around in two dimensions right now. If you want three dimenswions maybe make a new class.
 */
class Actor {
public:
    int alive;
    union {
        class {
        public:
            sf::Vector2f position;
            sf::Vector2f velocity;
        } live;
        Actor *next;
    } state;


};

#endif
