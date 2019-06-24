#ifndef PANEL_H
#define PANEL_H

#include "../Widget.hh"
#include "../Config.hh"
#include <forward_list>
#include <SFML/Graphics.hpp>

/**
 * A widget which is a visibly rendered box which contains other widgets.
 * TODO: make border thickness configurable.
 */
class Panel: public Widget {
    sf::VertexArray vertices;
    std::forward_list<Widget *> children;
    int vertical;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    constexpr static int const BORDER = 5;

    Panel(Config const *config, int vertical);

    virtual int onEvent(sf::Event *e) override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::FloatRect bounds) override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;
};

#endif
