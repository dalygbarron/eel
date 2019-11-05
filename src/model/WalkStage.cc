#include "model/WalkStage.hh"
#include "static/spdlog/spdlog.h"
#include "static/spdlog/bin_to_hex.h"

WalkStage::WalkStage(
    sf::Color bg,
    Asset<Tileset> const &tileset,
    sf::Vector2u chunkSize,
    sf::Vector2u tileSize
):
    bg(bg),
    tileset(tileset),
    chunkSize(chunkSize),
    tileSize(tileSize)
{
    // Doesn't do a whole lot.
}

WalkStage::WalkStage(WalkStage const &walkStage):
    bg(walkStage.bg),
    tileset(walkStage.tileset),
    chunkSize(walkStage.chunkSize),
    tileSize(walkStage.tileSize)
{
    for (auto const &chunkItem: walkStage.chunks) {
        this->chunks.emplace(chunkItem.first, walkStage.chunkSize);
        std::vector<Slice const *> slices = chunkItem.second.getSlices();
        for (auto const slice: slices) {
            if (slice) this->addSlice(chunkItem.first, *slice);
        }
    }
}

void WalkStage::addSlice(sf::Vector2i pos, Slice const &slice) {
    char lineBuffer[slice.size.x * 2 + 1];
    lineBuffer[0] = 0;
    spdlog::debug(
        "Adding slice ({}, {}, {}) ({}, {})",
        pos.x,
        pos.y,
        slice.height,
        slice.size.x,
        slice.size.y
    );
    for (int i = 0; i < slice.size.y; i++) {
        int offset = 0;
        for (int x = 0; x < slice.size.x; x++) {
            offset += sprintf(
                lineBuffer + offset,
                "%02x",
                slice.data.get()[i * slice.size.x + x] & 0xff
            );
        }
        lineBuffer[offset] = 0;
        spdlog::debug(lineBuffer);
    }
    if (this->chunks.count(pos) == 0) {
        this->chunks.emplace(pos, this->chunkSize);
    }
    this->chunks.at(pos).addSlice(slice);
}

void WalkStage::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.clear(this->bg);
}
