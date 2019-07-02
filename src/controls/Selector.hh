#ifndef SELECTOR_H
#define SELECTOR_H

#include "../Control.hh"

/**
 * Lets you select from a bunch of options and returns the index of the chosen option.
 */
class Selector: public Control {
public:
    /**
     * Creates the selector initially.
     */
    Selector();

    virtual int onEvent(sf::Event *e) override;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) const override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;
};

#endif
