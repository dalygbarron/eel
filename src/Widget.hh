#ifndef WIDGET_H
#define WIDGET_H

/**
 * General superclass for gui widgets.
 */
class Widget: public sf::Drawable, public sf::Transformable  {
    sf::Vector2f dimensions;

public:
    virtual int update();
};

#endif
