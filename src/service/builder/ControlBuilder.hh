#ifndef BUILDER_H
#define BUILDER_H

#include "model/control/Control.hh"
#include "static/Utils.hh"
#include "service/Config.hh"
#include "service/Repository.hh"

/**
 * Puts gui windows together according to your specifications.
 */
class ControlBuilder {
    Repository *repository;
    sf::Texture *bg;
    sf::Texture *fg;
    int border;
    int fontSizeNormal;
    int fontSizeBig;
    sf::Vector2i screen;

public:
    /**
     * Makes the builder and injects dependencies.
     * @param repository is the game's source of assets to use.
     * @param config     is the game's base configuration.
     */
    ControlBuilder(Repository *repository, Config const *config);

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
};

#endif
