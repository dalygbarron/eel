#ifndef CONTROL_H
#define CONTROL_H

#include <SFML/Graphics.hpp>

/**
 * General superclass for gui widgets.
 */
class Control: public sf::Drawable {
    public:
        /**
         * Virtual destructor so that controls can delete their children and
         * such.
         */
        virtual ~Control();

        /**
         * Updates the control.
         * @param mouse is a set of bytes for what mouse buttons have just been
         *              pressed.
         */
        virtual int update(unsigned char mouse);

        /**
         * Describes the given widget in text.
         * @return the textual description which you do not need to free.
         */
        virtual char const &getDescription() const = 0;

        /**
         * Gives you the size that a gui element would like to have, so that
         * it's parent element can size itself appropriately without being
         * greedy.
         * @return a rect of the dimensions that this element kinda needs to
         *         have ideally.
         */
        virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) const = 0;

        /**
         * Resize and build the widget's visual representation. This has to be
         * called once before the widget can be rendered properly. Should
         * recursively run on any child widgets, passing in whatever space is
         * left as bounds. Also this should set the dimensions field to
         * whatever the new dimensions are.
         * @param bounds is the area that the widget must fit inside. It does
         *               not have to use all of this space, and if it does then
         *               there will be no space for others. Be considerate.
         * @return the new bounds for convenience.
         */
        virtual sf::FloatRect resize(sf::FloatRect bounds) = 0;

    protected:
        sf::FloatRect dimensions;

    private:
        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override = 0;
};

#endif
