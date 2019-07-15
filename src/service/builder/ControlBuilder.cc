#include "service/builder/ControlBuilder.hh"
#include "model/control/Panel.hh"
#include "model/control/TextBox.hh"
#include "model/control/Bopper.hh"

ControlBuilder::ControlBuilder(Repository *repository, Config const *config) {
    this->repository = repository;
    this->fg = sf::Color(Utils::parseInt(config->get("fg")));
    this->bg = sf::Color(Utils::parseInt(config->get("bg")));
    this->highlight = sf::Color(Utils::parseInt(config->get("highlight")));
    this->border = Utils::parseInt(config->get("border"));
    this->fontSizeNormal = Utils::parseInt(config->get("fontNormal"));
    this->fontSizeBig = Utils::parseInt(config->get("fontBig"));
    this->screenWidth = Utils::parseInt(config->get("width"));
    this->screenHeight = Utils::parseInt(config->get("height"));
}

Control *ControlBuilder::speechBox(char const *name, char const *text) const {
    Panel *panel = new Panel(true, this->border, Panel::BORDER_VERTICAL, this->fg, this->bg);
    TextBox *nameBox = new TextBox(name, this->highlight, this->fontSizeBig);
    TextBox *textBox = new TextBox(text, this->fg, this->fontSizeNormal);
    panel->addChild(nameBox);
    panel->addChild(textBox);
    panel->addChild(new Bopper(this->fg));
    panel->resize(sf::FloatRect(
        this->screenWidth / 4,
        this->screenHeight / 4 * 3,
        this->screenWidth / 2,
        this->screenHeight / 4
    ));
    return panel;
}

Control *ControlBuilder::declarationBox(char const *text) const {
    Panel *panel = new Panel(true, this->border, Panel::BORDER_VERTICAL, this->fg, this->bg);
    TextBox *textBox = new TextBox(text, this->fg, this->fontSizeNormal);
    panel->addChild(textBox);
    panel->addChild(new Bopper(this->fg));
    panel->resize(sf::FloatRect(
        this->screenWidth / 4,
        this->screenHeight / 4 * 3,
        this->screenWidth / 2,
        this->screenHeight / 4
    ));
    return panel;
}
