#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Config.hh"
#include "Store.hh"

/**
 * Class for rendering many copies of a sprite from a spritesheet at the same time. Technically it can also do one I
 * think.
 */
class SpriteBatch: public Store<sf::IntRect>, public sf::Texture {
public:
    /**
     * Loads up the file and all that.
     * @param file is the file that is has to load the sprite batch from.
     * @param n    is the number of sprites it will be able to draw.
     */
    SpriteBatch(char const *file);

    /**
     * makes a quad which is fit to the size of the given sprite and angle and shit.
     * @param vertices   is a pointer to the 4 verticies making up the quad.
     * @param spriteName is the name of the sprite to build.
     * @param position   is where on the screen the centre of the quad will be.
     * @param angle      is the angle at which the quad should be turned.
     */
    void buildQuad(sf::Vertex *vertices, char const *spriteName, sf::Vector2f position, float angle);

    /**
     * Fits a named sprite onto the given quad.
     * @param vertices   is a pointer to the start of the quad.
     * @param spriteName is the name of the sprite to fit onto the quad.
     */
    void fitQuad(sf::Vertex *vertices, char const *spriteName);
};

#endif
