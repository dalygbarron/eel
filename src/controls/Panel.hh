#ifndef PANEL_H
#define PANEL_H

#include "../Control.hh"
#include "../Config.hh"
#include <SFML/Graphics.hpp>
#include <list>

/**
 * A widget which is a visibly rendered box which contains other widgets.
 * TODO: make border thickness configurable.
 */
class Panel: public Control {
    sf::VertexArray vertices;
    std::list<Control *> children;

public:
    constexpr static int const BORDER_VERTICAL = 0;
    constexpr static int const BORDER_HORIZONTAL = 1;

    int vertical;
    float border;
    int borderMode;
    sf::Color fg;
    sf::Color bg;

    /**
     * Default constructor that does not configure anything.
     */
    Panel();

    /**
     * Create and configure a panel.
     * @param vertical tells the panel whether to stack children vertically or horizontally.
     * @param border     is how thinck the panel's border should be.
     * @param borderMode is the style the border should be done in.
     * @param fg         is the colour with which to render the panel's border.
     * @param bg         is the colour with which to render the panel's back part.
     */
    Panel(int vertical, float border, int borderMode, sf::Color fg, sf::Color bg);

    virtual int onEvent(sf::Event *e) override;

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) const override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;

    /**
     * Adds a control onto this panel.
     * @param child is the child to add.
     */
    void addChild(Control *child);
};

#endif
