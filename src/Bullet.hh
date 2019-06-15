#ifndef BULLET_H
#define BULLET_H

#include <SFML/System.hpp>


/**
 * A bullet that flies around and shoots people.
 */
class Bullet {
public:
    int alive;
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::Vector2f gravity;
    float angle;
    union {
        // It's parameters when alive.
        struct {
            float radius;
            float speed;
            int shape;
            char *sprite;
        } live;
        // It's list pointer when dead.
        Bullet *next;
    } state;

    /**
     * Makes this bullet a rip off of another bullet's nature, so not it's position and such, but it's radius and speed
     * and shape.
     * @param bullet is the bullet to copy.
     */
    void copy(Bullet const *bullet);

    /**
     * Gives bullet a new trajectory. The speed will be the bullet's stored speed.
     * @param angle is the angle for it to move in.
     */
    void launch(float angle);

    /**
     * Gives bullet's gravity a new trajectory.
     * @param angle is the angle that the gravity is in.
     * @param rate  is the rate of acceleration the gravity will cause as a 1 dimensional speed along the angle.
     */
    void gravityLaunch(float angle, float rate);
};

#endif
