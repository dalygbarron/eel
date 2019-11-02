#ifndef PANEL_H
#define PANEL_H

#include "model/control/Control.hh"
#include "service/Config.hh"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * A widget which is a visibly rendered box which contains other widgets.
 */
class Panel: public Control {
    public:
        /**
         * Create and configure a panel.
         * @param vertical tells the panel whether to stack childre vertically
         * or horizontally.
         * @param border   is how thinck the panel's border should be.
         * @param texture  is the texture to draw in the box.
         */
        Panel(int vertical, float border, sf::Texture const &texture);

        /**
         * Adds a control onto this panel.
         * @param child is the child to add.
         */
        void addChild(Control &child);

        virtual int update(unsigned char mouse) override;

        virtual char const &getDescription() const override;

        virtual sf::Vector2f getDesiredSize(
            sf::Vector2f bounds
        ) const override;

        virtual sf::FloatRect resize(sf::FloatRect bounds) override;

    private:
        sf::RectangleShape box;
        std::vector<Control *> children;
        int vertical;
        float border;
        sf::Color fg;
        sf::Color bg;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;
};

#endif
