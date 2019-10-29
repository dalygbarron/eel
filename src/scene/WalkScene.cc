#include "scene/WalkScene.hh"

WalkScene::WalkScene(
    Engine const *engine,
    Asset<TileMap> const *map
): Scene(engine) {
    engine->joinRatPack(
        engine->config->get("spritesheet"),
        engine->config->get("tileset-slot"),
        map->get()->getTileset()->get()->getTexture()->get()
    );
    this->sprites = engine->getRatPackRepository()->get(
        engine->config->get("spritesheet")
    );
    this->background.setTexture(*this->sprites->get()->getTexture());
    this->background.setTextureRect(this->sprites->get()->getRat("tileset"));
}

WalkScene::~WalkScene() {
    // TODO: delete junk.
}

sf::Vector2i WalkScene::sortMobs() {
    sf::Vector2i dirty(0, 0);
    // TODO: implement a nice adaptive sort. Timsort sounds easy.
    //       in the process of doing this sort we also need to check which mobs
    //       have got their dirty flag set and set the dirty region to reflect
    //       that too. Also, so we don't need to iterate over this shit twice,
    //       we can also set their dirty flag back to false again.
    return dirty;
}

void WalkScene::logic(float delta) {
    // TODO: update walkstage.
}

void WalkScene::render(
    sf::RenderTarget *target,
    sf::RenderStates states
) const {
    target->clear(sf::Color::Cyan);
    target->draw(this->background);
}

void WalkStage::refocus(sf::Vector2f newFocus) {
    this->focus = newFocus;
    if (!this->focusChunk->contains(newFocus)) {
        this->focusChunk = this->chunks.at(
            newFocus / this->map->getTileSize() / this->focusChunk->getSize()
        );
        // TODO: this is where new chunk tiles get added to override the old.
    }
}

