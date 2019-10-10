#include "scene/WalkScene.hh"

WalkScene::WalkScene(Engine const *engine, TileMap *map): Scene(engine) {
    this->map = map;
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
    this->map->render(target, states);
}
