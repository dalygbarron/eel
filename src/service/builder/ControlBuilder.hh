#ifndef BUILDER_H
#define BUILDER_H

#include "model/control/Control.hh"
#include "service/Config.hh"
#include "service/repository/Repository.hh"
#include <SFML/Graphics.hpp>

/**
 * Puts gui windows together according to your specifications.
 */
class ControlBuilder {
    public:
        /**
         * Makes the builder and injects dependencies.
         * TODO: it would probably be better to get rid of this constructor and
         *       just make the thing configurable with methods, but we can do
         *       that another day.
         * @param textureRepo is the game's source of textures to use. TODO:
         *                    really shouldn't be passed in like this imo but
         *                    we can put up with it for now.
         * @param config      is the game's base configuration.
         */
        ControlBuilder(
            Repository<sf::Texture> *textureRepo,
            Config const *config
        );

        /**
         * Makes a box containing speech.
         * @param name is the name of the speaking person.
         * @param text is what they are saying.
         * @return the new box.
         */
        Control *speechBox(char const *name, char const *text) const;

        /**
         * Makes a box containing unattributed text.
         * @param text is the text in the box.
         * @return the new box.
         */
        Control *declarationBox(char const *text) const;

    private:
        Asset<sf::Texture> const *bg;
        Asset<sf::Texture> const *fg;
        int border;
        int fontSizeNormal;
        int fontSizeBig;
        sf::Vector2i screen;
};

#endif
