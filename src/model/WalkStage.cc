#include "model/WalkStage.hh"

WalkStage::WalkStage() {
    // will do stuff one day I assume.
}

WalkStage::WalkStage(WalkStage const *walkStage) {
    // Will also do stuff one day I imagine.
}

void WalkStage::render(sf::RenderTarget const *target) {

}

void tiledMap(sf::Vector2u size, sf::Vector2u tileSize, sf::Color bg) {
    this->bg = bg;
}

void tiledTileset(Asset<Tileset> const *tileset) {
    this->tileset = tileset;
}

void tiledLayer() {

}

void tiledChunk() {

}
