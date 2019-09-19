#include "service/builder/ControlBuilder.hh"
#include "model/control/Panel.hh"
#include "model/control/TextBox.hh"
#include "model/control/Bopper.hh"

ControlBuilder::ControlBuilder(Repository *repository, Config const *config) {
    this->repository = repository;
    this->fg = repository->getTexture(config->get("fg"));
    this->bg = repository->getTexture(config->get("bg"));
    this->border = Utils::parseInt(config->get("border"));
    this->fontSizeNormal = Utils::parseInt(config->get("fontNormal"));
    this->fontSizeBig = Utils::parseInt(config->get("fontBig"));
    this->screenWidth = Utils::parseInt(config->get("width"));
    this->screenHeight = Utils::parseInt(config->get("height"));
}

Control *ControlBuilder::speechBox(char const *name, char const *text) const {
    Panel *panel = new Panel(true, this->border, this->bg);
    TextBox *nameBox = new TextBox(name, this->fontSizeBig);
    TextBox *textBox = new TextBox(text, this->fontSizeNormal);
    panel->addChild(nameBox);
    panel->addChild(textBox);
    panel->addChild(new Bopper());
    panel->resize(sf::FloatRect(
        this->screenWidth / 4,
        this->screenHeight / 4 * 3,
        this->screenWidth / 2,
        this->screenHeight / 4
    ));
    return panel;
}

Control *ControlBuilder::declarationBox(char const *text) const {
    Panel *panel = new Panel(true, this->border, this->bg);
    TextBox *textBox = new TextBox(text, this->fontSizeNormal);
    panel->addChild(textBox);
    panel->addChild(new Bopper());
    panel->resize(sf::FloatRect(
        this->screenWidth / 4,
        this->screenHeight / 4 * 3,
        this->screenWidth / 2,
        this->screenHeight / 4
    ));
    return panel;
}
