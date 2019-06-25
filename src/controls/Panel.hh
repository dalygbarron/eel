#ifndef PANEL_H
#define PANEL_H

#include "Control.hh"
#include "../Config.hh"
#include <forward_list>
#include <SFML/Graphics.hpp>

/**
 * A widget which is a visibly rendered box which contains other widgets.
 * TODO: make border thickness configurable.
 */
class Panel: public Control {
    sf::VertexArray vertices;
    std::forward_list<Control *> children;
    int vertical;
    float border;
    sf::Color fg;
    sf::Color bg;

public:
    /**
     * Create and configure a panel.
     * @param vertical tells the panel whether to stack children vertically or horizontally.
     * @param border   is how thinck the panel's border should be.
     * @param fg       is the colour with which to render the panel's border.
     * @param bg       is the colour with which to render the panel's back part.
     */
    Panel(int vertical, float border, sf::Color fg, sf::Color bg);

    virtual int onEvent(sf::Event *e) override;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;

    /**
     * Adds a control onto this panel.
     * @param child is the child to add.
     */
    void addChild(Control *child);
};

#endif
