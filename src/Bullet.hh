#ifndef BULLET_H
#define BULLET_H

/**
 * A bullet that flies around and shoots people.
 */
class Bullet {
public:
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::Vector2f gravity;
    float angle = 0;
    int alive = false;

    /**
     * Gives bullet a new trajectory.
     * @param angle is the angle for it to move in.
     * @param speed is the speed for it to move at.
     */
    void launch(float angle, float speed);

    /**
     * Gives bullet's gravity a new trajectory.
     * @param angle is the angle that the gravity is in.
     * @param speed is the rate of acceleration the gravity will cause as a 1 dimensional speed along the angle.
     */
    void gravityLaunch(float angle, float speed);
};

#endif
