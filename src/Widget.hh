#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>

/**
 * General superclass for gui widgets.
 */
class Widget: public sf::Drawable {
    sf::FloatRect dimensions;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

public:
    /**
     * Creates the widget and tells it what it's bounds and it's offset are.
     * @param dimensions are the dimensions of the widget. I reserve the right to dynamically alter the width and height
     *                   after it's been set.
     */
    Widget(sf::FloatRect dimensions);

    /**
     * Allows the widget to respond to an event.
     * @param e is the event to respond to. It should only really be user input events.
     * @return a non negative value to signify something is happening.
     */
    virtual int onEvent(sf::Event *e) = 0;

    /**
     * Describes the given widget in text.
     * @return the textual description which you do not need to free.
     */
    virtual char *getDescription() = 0;
};

#endif
