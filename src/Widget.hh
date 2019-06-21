#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>

/**
 * General superclass for gui widgets.
 */
class Widget: public sf::Drawable {
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

protected:
    sf::FloatRect dimensions;

public:
    /**
     * Allows the widget to respond to an event.
     * @param e is the event to respond to. It should only really be user input events.
     * @return a non negative value to signify something is happening.
     */
    virtual int onEvent(sf::Event *e);

    /**
     * Describes the given widget in text.
     * @return the textual description which you do not need to free.
     */
    virtual char const *getDescription() = 0;

    /**
     * Resize and build the widget's visual representation. This has to be called once before the widget can be rendered
     * properly. Should recursively run on any child widgets, passing in whatever space is left as bounds. Also this
     * should set the dimensions field to whatever the new dimensions are.
     * @param bounds is the area that the widget must fit inside. It does not have to use all of this space, and if it
     *               does then there will be no space for others. Be considerate.
     * @return the new bounds for convenience.
     */
    virtual sf::FloatRect resize(sf::FloatRect bounds) = 0;
};

#endif
