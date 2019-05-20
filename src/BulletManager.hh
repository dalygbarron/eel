#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <SFML/Graphics.hpp>
#include "Config.hh"

/**
 * Manages all the bullets that are going. draws them and does their collisions and shit.
 */
class BulletManager: public sf::Drawable, public sf::Transformable {
    Bullet bullets[Config::BULLET_LIMIT];
    sf::VertexArray vertices;
    sf::Texture sprite;

    /**
     * @Override
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    /**
     * Creates the bullet manager and puts shit on the GPU.
     * @param file is the file to load the info about bullets from. This info tells us what image to use and what each
     *             bullet is like.
     */
    BulletManager(char const *file);

    /**
     * Moves all the bullets in appropriate ways.
     * @see Config::FRAME_RATE.
     */
    void update();
};

#endif
