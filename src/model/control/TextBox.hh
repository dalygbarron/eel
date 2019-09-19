#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "model/control/Control.hh"
#include "static/Constant.hh"

/**
 * A textbox that just shows some text.
 */
class TextBox: public Control {
    public:
        /**
         * Sets the content of the text box and processes it a little bit maybe
         * to make it fit.
         * @param content is the text to show.
         * @param size    is the size to make the text be.
         */
        TextBox(char const *content, float size);

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
        char const *content;
        sf::RectangleShape box;
        sf::Text text;
        sf::Font font;
};

#endif
