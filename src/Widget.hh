#ifndef WIDGET_H
#define WIDGET_H

/**
 * General superclass for gui widgets.
 */
class Widget: public sf::Drawable, public sf::Transformable  {
    sf::Vector2f dimensions;

public:
    /**
     * Updates the widget so that it can interact with the user or whatever it wants to do.
     */
    virtual int update();
};

#endif
