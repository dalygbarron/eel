#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <SFML/Graphics.hpp>

/**
 * Manages all the bullets that are going. draws them and does their collisions and shit.
 */
class BulletManager: public sf::Drawable, public sf::Transformable {

public:
    /**
     * Creates the bullet manager.
     * @param file is the file to load the info about bullets from. This info tells us what image to use and what each
     *             bullet is like.
     */
    BulletManager(char const *file);

    /**
     *
    void update();

    void render();

};

#endif
