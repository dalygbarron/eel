#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Config.hh"
#include "SpriteBatch.hh"
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

/**
 * Loads assets out of files and then keeps them stored for later.
 * Could potentially add strategic dropping of little used data if memory usage is an issue.
 */
class Repository {
    Config const *config;
    sf::Font font;
    std::unordered_map<std::string, sf::Texture *> textures;
    std::unordered_map<std::string, SpriteBatch *> spriteBatches;

public:
    /**
     * Creates the repository.
     * @param config is the configuration which the repo uses to get the dir for files.
     */
    Repository(Config const *config);
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
     * Gives you the game's font.
     * @return the font which was decided in the game's main config file.
     */
    sf::Font const *getFont();
};

#endif
