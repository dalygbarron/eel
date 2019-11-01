#include "model/WalkStage.hh"

WalkStage::WalkStage() {
    // will do stuff one day I assume.
}

WalkStage::WalkStage(WalkStage const *walkStage) {
    // Will also do stuff one day I imagine.
}

void WalkStage::tiledMap(
    sf::Vector2u size,
    sf::Vector2u tileSize,
    sf::Color bg
) {
    this->bg = bg;
}

void WalkStage::tiledTileset(Asset<Tileset> const *tileset) {
    this->tileset = tileset;
}

Asset<Tileset> const *WalkStage::getTileset() const {
    return this->tileset;
}

void WalkStage::tiledLayer() {

}

void WalkStage::tiledChunk() {

}

void WalkStage::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.clear(this->bg);
}
