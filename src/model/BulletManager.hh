#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "model/Bullet.hh"
#include "model/SpriteBatch.hh"
#include "static/Constant.hh"
#include "service/Repository.hh"
#include "service/Config.hh"
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

/**
 * Manages all the bullets that are going. draws them and does their collisions and shit.
 * TODO: making this a top level thing is not reentrant, so it should be made one per scene that uses it.
 */
class BulletManager: private Store<Bullet *>, public sf::Drawable, public sf::Transformable {
    Repository *repository;
    Bullet bullets[Constant::BULLET_LIMIT];
    Bullet *empty;
    std::unordered_map<std::string, Bullet *> prototypes;
    SpriteBatch *sprites;
    sf::VertexArray vertices;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    /**
     * Creates the bullet manager and puts shit on the GPU.
     * @param config     is the game configuration used to find the bullets file and stuff.
     * @param repository is used to load the bullet assets.
     */
    BulletManager(Config const *config, Repository *repository);

    /**
     * Moves all the bullets in appropriate ways.
     * @see FRAME_RATE.
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
     * @param position  is the starting position to put it at.
     * @return a pointer to the new bullet.
     */
    Bullet *addBullet(Bullet const *prototype, sf::Vector2f position);

    /**
     * Callback function used to populate the bullet manager's data from an ini file.
     * @param reference is a reference to the bullet manager that is being built.
     * @param section   is the section that the current piece of data was in.
     * @param name      is the name of the current piece of data to add.
     * @param value     is the value of the current piece of data to add.
     * @return 1 if all is going well, and another value if not.
     */
    static int handleIni(void *reference, char const *section, char const *name, char const *value);
};

#endif
