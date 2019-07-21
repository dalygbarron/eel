#ifndef BULLET_H
#define BULLET_H

/**
 * Represents a bullet that flies about the place.
 */
struct Bullet {
    // Current position of the bullet.
    sfVector2f pos;

    // Current movement rate of the bullet per frame.
    sfVector2f velocity;

    // Name of the sprite used to draw this kind of bullet.
    char const *sprite;

    // Natural speed of this kind of bullet.
    float speed;
};

#endif
