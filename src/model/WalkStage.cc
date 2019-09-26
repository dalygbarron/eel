#include "model/WalkStage.hh"

WalkStage::WalkStage(TileMap const *start) {
    this->map = start;
    this->sector = map;
}

WalkStage::~WalkStage() {
    delete this->mobs;
    delete this->tiles;
    delete this->actors;
    delete this->placements;
    delete this->bullets;
    // TODO: memory leak.
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

void WalkStage::update(Engine *engine, float delta) {
    for (int i = 0; i < this->nActors; i++) {
        this->actors[i]->update(engine, delta);
    }
    for (int i = 0; i < this->nBullets; i++) {
        this->bullets[i]->update(delta);
    }
    for (int i = 0; i < this->nPlacements; i++) {
        this->placements[i]->update(engine, delta);
    }


}

void WalkStage::render(sf::RenderTarget &target, sf::RenderStates states) {
    target.draw(this->buffer);
}
