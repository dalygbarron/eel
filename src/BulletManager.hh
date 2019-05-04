#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "Texture.hh"
#include "Vector.hh"

/**
 * Represents a bullet that moves about the place.
 */
class Bullet {
public:
    Vector2 pos;
    Vector2 velocity;
    Vector2 gravity;
    Vector3 colour;
    float angle;
    unsigned char type = 0;
};

/**
 * Contains a bunch of bullets, pools them, processes them, and renders them efficiently.
 */
class BulletManager {
public:
    static const int MAX_BULLETS = 1280;

private:
    Bullet bullets[BulletManager::MAX_BULLETS];
    Texture const *texture;

public:
    /**
     * Creates the bullet manager with it's nice picture.
     * @param texture is the texture to draw the bullets with.
     */
    BulletManager(Texture const *texture);

    /**
     * Moves all the bullets.
     */
    void process();

    /**
     * Renders all the bullets to the screen.
     */
    void render();
};

#endif
