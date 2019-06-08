#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <SFML/Graphics.hpp>
#include "SpriteBatch.hh"

/**
 * Loads assets out of files and then keeps them stored for later.
 * Could potentially add strategic dropping of little used data if memory usage is an issue.
 */
class Repository {
public:
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
};

#endif
