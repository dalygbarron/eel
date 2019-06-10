#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.hh"
#include "SpriteBatch.hh"

/**
 * Loads assets out of files and then keeps them stored for later.
 * Could potentially add strategic dropping of little used data if memory usage is an issue.
 */
class Repository {
    Game const *game;
    std::unordered_map<std::string, sf::Texture *> textures;
    std::unordered_map<std::string, SpriteBatch *> spriteBatches;

public:
    /**
     * Creates the repository.
     * @param game is the game which the repo uses to get the dir for files.
     */
    Repository(Game const *game);
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
