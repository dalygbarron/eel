#ifndef PANEL_H
#define PANEL_H

#include "model/control/Control.hh"
#include "service/Config.hh"
#include <SFML/Graphics.hpp>
#include <list>

/**
 * A widget which is a visibly rendered box which contains other widgets.
 */
class Panel: public Control {
    public:
        constexpr static int const BORDER_VERTICAL = 0;
        constexpr static int const BORDER_HORIZONTAL = 1;

        /**
         * Default constructor that does not configure anything.
         */
        Panel();

        /**
         * Create and configure a panel.
         * @param vertical   tells the panel whether to stack children
         *                   vertically or horizontally.
         * @param border     is how thinck the panel's border should be.
         * @param borderMode is the style the border should be done in.
         * @param fg         colour to render the panel's border with.
         * @param bg         colour to render panel body with.
         */
        Panel(
            int vertical,
            float border,
            int borderMode,
            sf::Color fg,
            sf::Color bg
        );

        /**
         * Adds a control onto this panel.
         * @param child is the child to add.
         */
        void addChild(Control *child);

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
        std::list<Control *> children;
        int vertical;
        float border;
        int borderMode;
        sf::Color fg;
        sf::Color bg;
};

#endif
