#include "model/WalkStage.hh"

WalkStage::WalkStage() {
    // Doesn't do a whole lot.
}

WalkStage::WalkStage(WalkStage const *walkStage) {
    this->bg = walkStage->bg;
}

void WalkStage::tiledMap(
    sf::Vector2u size,
    sf::Vector2u tileSize,
    sf::Color bg
) {
    this->bg = bg;
}

Asset<Tileset> const *WalkStage::getTileset() const {
    return this->tileset;
}

void WalkStage::tiledTileset(Asset<Tileset> const &tileset) {
    this->tileset = &tileset;
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
