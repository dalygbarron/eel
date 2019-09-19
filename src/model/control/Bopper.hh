#ifndef BOPPER_H
#define BOPPER_H

#include "model/control/Control.hh"

/**
 * A thing that simply returns as soon as an appropriate button is clicked.
 * TODO: we should probably make this thing have variable size, or make it
 *       invisible or something because at the moment it's massive.
 */
class Bopper: public Control {
    public:
        /**
         * Creates the bopper.
         * @param colour the colour to draw it in.
         */
        Bopper(sf::Color colour);

        virtual int update(unsigned char mouse) override;

        virtual void render(
            sf::RenderTarget *target,
            sf::RenderStates states
        ) const override;

        virtual char const *getDescription() const override;

        virtual sf::Vector2f getDesiredSize(
            sf::Vector2f bounds
        ) const override;

        virtual sf::FloatRect resize(sf::FloatRect bounds) override;
    private:
        sf::VertexArray vertices;
        sf::Color colour;
};

#endif
