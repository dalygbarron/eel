#ifndef BUTTON_H
#define BUTTON_H

/**
 * Represents a button which is clicked with the mouse and contains arbitrary
 * stuff and returns an arbitrary predefined value when clicked.
 */
class Button: public Control {
    public:
        /**
         * Creates a button.
         * @param id      is the value it will return when clicked.
         * @param content is the control it will display inside itself.
         */
        Button(int id, Control *content);

        /**
         * Destroys the button.
         */
        ~Button();

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
        Control *content;
        int id;
        int highlighted;
        sf::Color fg;
        sf::Color bg;
        sf::Color highlight;
};

#endif
