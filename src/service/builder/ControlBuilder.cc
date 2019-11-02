#include "service/builder/ControlBuilder.hh"
#include "static/Utils.hh"
#include "model/control/Panel.hh"
#include "model/control/TextBox.hh"
#include "model/control/Bopper.hh"

ControlBuilder::ControlBuilder(
    Repository<sf::Texture> &textureRepo,
    Config const &config
):
    fg(textureRepo.get(config.getOption(*"fg"))),
    bg(textureRepo.get(config.getOption(*"bg")))
{
    this->border = Utils::parseInt(config.getOption(*"border"));
    this->fontSizeNormal = Utils::parseInt(config.getOption(*"fontNormal"));
    this->fontSizeBig = Utils::parseInt(config.getOption(*"fontBig"));
    this->screen = config.dimensions;
}

Control &ControlBuilder::speechBox(char const &name, char const &text) const {
    Panel *panel = new Panel(true, this->border, this->bg.get());
    TextBox *nameBox = new TextBox(name, this->fontSizeBig);
    TextBox *textBox = new TextBox(text, this->fontSizeNormal);
    panel->addChild(*nameBox);
    panel->addChild(*textBox);
    panel->addChild(*(new Bopper()));
    panel->resize(sf::FloatRect(
        this->screen.x / 4,
        this->screen.y / 4 * 3,
        this->screen.x / 2,
        this->screen.y / 4
    ));
    return *panel;
}

Control &ControlBuilder::declarationBox(char const &text) const {
    Panel *panel = new Panel(true, this->border, this->bg.get());
    TextBox *textBox = new TextBox(text, this->fontSizeNormal);
    panel->addChild(*textBox);
    panel->addChild(*(new Bopper()));
    panel->resize(sf::FloatRect(
        this->screen.x / 4,
        this->screen.y / 4 * 3,
        this->screen.x / 2,
        this->screen.y / 4
    ));
    return *panel;
}
