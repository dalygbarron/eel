#ifndef RAT_PACK_H
#define RAT_PACK_H

#include <vector>

/**
 * Fits a whole ratpack file of sprites and lets you put those sprites onto
 * quads whenever you so desire.
 */
class RatPack {
    public:
        /**
         * Creates the initial rat pack object by putting in it's texture but
         * without the rats yet as they must be added one by one with
         * a function call.
         * @param texture is the pack's texture.
         */
        RatPack(Asset<sf::Texture> const *texture);

        /**
         * Creates the right rat sprite thingy.
         * @param name     is the name of the sprite to make.
         * @param vertices is a pointer to the first of four vertices.
         */
        void makeRat(char const *name, sf::Vertex *vertices);

        /**
         * Adds another rat to the rat pack.
         * @param name is the name of the added rat.
         * @param shape is the position and size of the rat within the overall
         *        texture.
         */
        void addRat(char const *name, sf::IntRect shape);

    private:

        std::unordered_map<std::string, sf::IntRect> rats;
        Asset<sf::Texture> const *texture;
}

#endif
