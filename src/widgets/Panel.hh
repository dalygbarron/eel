#ifndef PANEL_H
#define PANEL_H

#include "../Widget.hh"

/**
 * A widget which is a visibly rendered box which contains other widgets.
 */
class Panel: public Widget {
    sf::VertexArray vertices;
    std::forward_list<Widget *> children;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    constexpr static int const BORDER = 5;

    Panel(sf::FloatRect dimensions, Config *config);

    virtual int onEvent(sf::Event *e) override;

};

#endif
