#include "Panel.hh"
#include "../Config.hh"
#include "../Utils.hh"

virtual void Panel::draw(sf::RenderTarget &target, sf::RenderStates states) const override {

}

Panel::Panel(sf::FloatRect dimensions, Config *config): widget(dimensions) {
    this->vertices(sf::Quads, 20);
    // set up the middle part
    this->vertices[0].position = sf::Vertex2f(dimensions.x + Panel::BORDER, dimensions.y + Panel::BORDER);
    this->vertices[1].position = sf::Vertex2f(dimensions.x + dimensions.w - Panel::BORDER, dimensions.y + Panel::BORDER);
    this->vertices[2].position = sf::Vertex2f(dimensions.x + dimensions.w - Panel::BORDER, dimensions.y + dimensions.h - Panel::BORDER);
    this->vertices[3].position = sf::Vertex2f(dimensions.x + Panel::BORDER, dimensions.y + dimensions.h - Panel::BORDER);
    this->vertices[0].color = sf::Color::Green;
    this->vertices[1].color = sf::Color::Green;
    this->vertices[2].color = sf::Color::Green;
    this->vertices[3].color = sf::Color::Green;
    // set up the border parts
    this->vertices[5].position = sf::Vertex2f(dimensions.x + Panel::BORDER, dimensions.y + Panel::BORDER);


}

virtual int Panel::onEvent(sf::Event *e) override {

}
