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
    for (sf::Vector2i const &pos: walkStage.chunks) {
        this->chunks.emplace(pos, walkStage.chunkSize);
        std::vector slices = walkStage.chunks(pos).getSlices();
        for (auto const &slice: slices) {
            this->addSlice(pos, slice);
        }
    }
}

void WalkStage::addSlice(sf::Vector2i pos, Slice &slice) {
    if (this->chunks.count(pos) == 0) {
        this->chunks.emplace(pos, this->chunkSize);
    }
    this->chunks[pos].addSlice(slice);
}

void WalkStage::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.clear(this->bg);
}
