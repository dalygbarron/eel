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
    if (this->chunks.count(pos) == 0) {
        this->chunks.emplace(pos, this->chunkSize);
    }
    this->chunks.at(pos).addSlice(slice);
}

std::vector<Slice const *> const *WalkStage::getSlices(
    sf::Vector2i pos
) const {
    if (this->chunks.count(pos) == 0) return 0;
    return &this->chunks.at(pos).getSlices();
}

void WalkStage::attach(PaneBuffer &paneBuffer) {
    for (int i = 0; i < WalkStage::MAX_TILES; i++) {
        this->tiles[i].attach(paneBuffer.claim());
    }
    for (int i = 0; i < WalkStage::MAX_BULLETS; i++) {
        this->bullets[i].attach(paneBuffer.claim());
    }
    for (int i = 0; i < WalkStage::MAX_ACTORS; i++) {
        this->actors[i].attach(paneBuffer.claim());
    }
    for (int i = 0; i < WalkStage::MAX_PLACEMENTS; i++) {
        this->placements[i].attach(paneBuffer.claim());
    }
}

void WalkStage::update(float delta) {
    for (int i = 0; i < WalkStage::MAX_ACTORS; i++) {
        if (this->actors[i].alive) {
            this->actors[i].update(delta);
            this->actors[i].logic(delta);
        }
    }
    for (int i = 0; i < WalkStage::MAX_BULLETS; i++) {
        if (this->bullets[i].alive) this->bullets[i].update(delta);
    }
}

Tile *WalkStage::addTile(unsigned char id, sf::Vector3f pos) {
    // TODO: this implementation is shit, I just can't be bothered right now.
    for (int i = 0; i < WalkStage::MAX_TILES; i++) {
        if (!this->tiles[i].alive) {
            this->tiles[i].restore(this->tileset.get(), id);
            this->tiles[i].place(pos);
            return this->tiles + i;
        }
    }
    return 0;
}

Bullet *WalkStage::addBullet(Cartridge const &proto, sf::Vector3f pos) {

}

Actor *WalkStage::addActor(Persona const &proto, sf::Vector3f pos) {
    // TODO: this implementation is shit, I just can't be bothered right now.
    for (int i = 0; i < WalkStage::MAX_ACTORS; i++) {
        if (!this->actors[i].alive) {
            Persona p;
            this->actors[i].restore(p);
            this->actors[i].place(pos);
            return this->actors + i;
        }
    }
    return 0;
}

Placement *WalkStage::addPlacement(Item const &proto, sf::Vector3f pos) {

}

void WalkStage::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.clear(this->bg);
}
