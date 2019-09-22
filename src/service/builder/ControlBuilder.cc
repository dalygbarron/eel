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
    this->screen = config->getDimensions();
}

Control *ControlBuilder::speechBox(char const *name, char const *text) const {
    Panel *panel = new Panel(true, this->border, this->bg);
    TextBox *nameBox = new TextBox(name, this->fontSizeBig);
    TextBox *textBox = new TextBox(text, this->fontSizeNormal);
    panel->addChild(nameBox);
    panel->addChild(textBox);
    panel->addChild(new Bopper());
    panel->resize(sf::FloatRect(
        this->screen.x / 4,
        this->screen.y / 4 * 3,
        this->screen.x / 2,
        this->screen.y / 4
    ));
    return panel;
}

Control *ControlBuilder::declarationBox(char const *text) const {
    Panel *panel = new Panel(true, this->border, this->bg);
    TextBox *textBox = new TextBox(text, this->fontSizeNormal);
    panel->addChild(textBox);
    panel->addChild(new Bopper());
    panel->resize(sf::FloatRect(
        this->screen.x / 4,
        this->screen.y / 4 * 3,
        this->screen.x / 2,
        this->screen.y / 4
    ));
    return panel;
}
