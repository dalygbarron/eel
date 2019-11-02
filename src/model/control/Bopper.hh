#ifndef BOPPER_H
#define BOPPER_H

#include "model/control/Control.hh"

/**
 * A thing that simply returns as soon as an appropriate button is clicked.
 * They are invisible.
 */
class Bopper: public Control {
    public:
        virtual int update(unsigned char mouse) override;

        virtual char const &getDescription() const override;

        virtual sf::Vector2f getDesiredSize(
            sf::Vector2f bounds
        ) const override;

        virtual sf::FloatRect resize(sf::FloatRect bounds) override;

    private:
        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;
};

#endif
