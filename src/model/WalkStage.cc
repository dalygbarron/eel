#include "model/WalkStage.hh"

WalkStage::WalkStage(
    sf::Color bg,
    Asset<Tileset> const &tileset,
    int layers,
    sf::Vector2u chunkSize,
    sf::Vector2i tileSize
):
    bg(bg),
    tileset(tileset),
    layers(layers),
    chunkSize(chunkSize),
    tileSize(tileSize)
{
    // Doesn't do a whole lot.
}

WalkStage::WalkStage(WalkStage const &walkStage):
    bg(walkStage.bg),
    tileset(walkStage.tileset),
    layers(walkStage.layers),
    chunkSize(walkStage.chunkSize),
    tileSize(walkStage.tileSize)
{
    for (std::pair<sf::Vector2i, unsigned char &> item: walkStage.chunks) {
        this->addChunk(item.first, item.second);
    }
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
