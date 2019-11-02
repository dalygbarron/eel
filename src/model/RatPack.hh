#ifndef RAT_PACK_H
#define RAT_PACK_H

#include "model/Asset.hh"
#include <SFML/Graphics.hpp>
#include <unordered_map>

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
         * @param texture is the pack's texture which is not const because it
         *                needs to be editable.
         */
        RatPack(sf::Texture &texture);

        /**
         * Gives you immutable access to the rat pack's texture so you can draw
         * with it in normal use cases.
         * @return the texture it uses.
         */
        sf::Texture const &getTexture() const;

        /**
         * Gives you access to the rat pack's texture. As you will notice, the
         * texture is mutable but that is fine because not just anybody will
         * have non const access to this here rat pack.
         * @return the texture used in a mutable form.
         */
        sf::Texture &getTextureMutable();

        /**
         * Creates the right rat sprite thingy.
         * @param name     is the name of the sprite to make.
         * @param vertices is a pointer to the first of four vertices.
         */
        void makeRat(char const &name, sf::Vertex &vertices) const;

        /**
         * Gives you the dimensions of the given rat.
         * @return a rectangle that covers it.
         */
        sf::IntRect getRat(char const &name) const;

        /**
         * Adds another rat to the rat pack.
         * @param name is the name of the added rat.
         * @param shape is the position and size of the rat within the overall
         *        texture.
         */
        void addRat(char const &name, sf::IntRect shape);

    private:
        std::unordered_map<std::string, sf::IntRect> rats;
        sf::Texture &texture;
};

#endif
