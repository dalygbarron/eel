#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Config.hh"

/**
 * Class for rendering many copies of a sprite from a spritesheet at the same time. Technically it can also do one I
 * think.
 */
class SpriteBatch {
    std::unordered_map<std::string, sf::IntRect> sprites;
    sf::Texture texture;

public:
    /**
     * Loads up the file and all that.
     * @param file is the file that is has to load the sprite batch from.
     * @param n    is the number of sprites it will be able to draw.
     */
    SpriteBatch(char const *file);

    /**
     * Fits a named sprite onto the given quad.
     * @param vertices   is a pointer to the start of the quad.
     * @param spriteName is the name of the sprite to fit onto the quad.
     */
    void fitQuad(sf::Vertex *vertices, char const *spriteName);

    /**
     * Gives you the sprite batch's texture for rendering.
     * @return the texture in it.
     */
    sf::Texture *getTexture();
};

#endif
