#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "Control.hh"

/**
 * A textbox that just shows some text.
 */
class Text: public Control {
    char const *content;

public:
    /**
     * Sets the content of the text box and processes it a little bit maybe to make it better.
     * @param content is the text to show.
     */
    Text(char const *content);

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;
};

#endif
