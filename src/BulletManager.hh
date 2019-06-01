#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include <string>
#include <unordered_map>
#include "Bullet.hh"
#include "Config.hh"
#include "SpriteBatch.hh"
#include <SFML/Graphics.hpp>

/**
 * Manages all the bullets that are going. draws them and does their collisions and shit.
 */
class BulletManager: public sf::Drawable, public sf::Transformable {
    Bullet bullets[Config::BULLET_LIMIT];
    Bullet *empty;
    std::unordered_map<std::string, Bullet *> prototypes;
    SpriteBatch *sprites;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

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

    /**
     * Gives you access to the bullet prototype of the given name.
     * @param type is the name of the prototype you want.
     * @return the prototype and it's constant so you can't fuck it up.
     */
    Bullet const *getPrototype(char const *type);

    /**
     * Create a new live bullet of a certain type.
     * @param prototype is a pointer to the prototypal bullet you want to create.
     * @return a pointer to the new bullet.
     */
    Bullet *addBullet(Bullet const *prototype);

    /**
     * Callback function used to populate the bullet manager's data from an ini file.
     * @param reference is a reference to the bullet manager that is being built.
     * @param section   is the section that the current piece of data was in.
     * @param name      is the name of the current piece of data to add.
     * @param value     is the value of the current piece of data to add.
     * @return 1 if all is going well, and another value if not.
     */
    friend int handleIni(void *reference, char const *section, char const *name, char const *value);
};

#endif
