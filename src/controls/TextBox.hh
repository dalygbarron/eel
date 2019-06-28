#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "Control.hh"
#include "../Constant.hh"

/**
 * A textbox that just shows some text.
 */
class TextBox: public Control {
    char const *content;
    sf::Text text;
    sf::Font font;

    /**
     * Fits the text box's content into the given bounds by using new lines and cutting words off the end, and then
     * saves it like that.
     * @param bounds are the bounds that the content must fit within.
     */
    void fitContent(sf::FloatRect bounds);

public:
    /**
     * Sets the content of the text box and processes it a little bit maybe to make it better.
     * @param content is the text to show.
     * @param size    is the size to make the text be.
     */
    TextBox(char const *content, float size);

    virtual void render(sf::RenderTarget *target, sf::RenderStates states) const override;

    virtual char const *getDescription() override;

    virtual sf::Vector2f getDesiredSize(sf::Vector2f bounds) const override;

    virtual sf::FloatRect resize(sf::FloatRect bounds) override;
};

#endif
