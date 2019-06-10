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
class SpriteBatch: public sf::Drawable, public sf::Transformable {
    std::unordered_map<std::string, sf::IntRect> sprites;
    sf::VertexArray vertices;
    sf::Texture texture;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    /**
     * Loads up the file and all that.
     * @param file is the file that is has to load the sprite batch from.
     */
    SpriteBatch(char const *file);
};

#endif
