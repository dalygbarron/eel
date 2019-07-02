#ifndef BUILDER_H
#define BUILDER_H

#include "Config.hh"
#include "Repository.hh"
#include "Utils.hh"
#include "Control.hh"

/**
 * Puts gui windows together according to your specifications.
 */
class Builder {
    Repository *repository;
    sf::Color bg;
    sf::Color fg;
    int border;
    int fontSizeNormal;
    int fontSizeBig;
    int screenWidth;
    int screenHeight;

public:
    /**
     * Makes the builder and injects dependencies.
     * @param repository is the game's source of assets to use.
     * @param config     is the game's base configuration.
     */
    Builder(Repository *repository, Config const *config);

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
