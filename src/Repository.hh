#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <SFML/Graphics.hpp>
#include "SpriteBatch.hh"
#include "BulletManager.hh"

/**
 * Globally accessible place where loaded in stuff like bullets and images and shit can be stored.
 */
namespace Repository {
    /**
     * Gives you a texture from a given file. After the first time it gets loaded it stores it for faster loading.
     * @param name is the filename of the texture.
     * @return the texture.
     */
    sf::Texture *getTexture(char const *name);

    /**
     * Gives you a sprite batch from a given file. After the first time it gets loaded it stores it for later.
     * @param name is the filename of the sprite batch.
     * @return the sprite batch.
     */
    SpriteBatch *getSpriteBatch(char const *name);

    /**
     * Gives you the bullet manager. If it has not been loaded yet then it loads it from a file.
     * @param name is the name of the file from which to load.
     */
    BulletManager *getBulletManager(char const *name);
};

#endif
