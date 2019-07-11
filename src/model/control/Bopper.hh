#ifndef BOPPER_H
#define BOPPER_H

#include "model/control/Control.hh"

/**
 * A thing that simply returns as soon as an appropriate button is clicked.
 */
class Bopper: public Control {
    sf::VertexArray vertices;
    sf::Color colour;

public:
    Bopper(sf::Color colour);

    virtual int onEvent(sf::Event *e) override;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) const override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;
};

#endif
