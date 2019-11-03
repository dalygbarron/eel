#include "model/WalkStage.hh"

WalkStage::WalkStage(
    sf::Color bg,
    Asset<Tileset> const &tileset,
    int layers,
    sf::Vector2u chunkDimensions
):
    bg(bg),
    tileset(tileset),
    layers(layers),
    chunkDimensions(chunkDimensions)
{
    // Doesn't do a whole lot.
}

WalkStage::WalkStage(WalkStage const &walkStage):
    bg(walkStage.bg),
    tileset(walkStage.tileset),
    layers(walkStage.layers),
    chunkDimensions(walkStage.chunkDimensions)
{
    // nothing else rn.
}

void WalkStage::addChunk(sf::Vector2i pos, unsigned char &tiles) {
    this->chunks.emplace(pos, tiles);
}

void WalkStage::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.clear(this->bg);
}
