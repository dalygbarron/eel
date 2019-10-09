#include "model/TileMap.hh"
#include "static/spdlog/spdlog.h"

TileMap::TileMap(sf::Vector2u tileSize, Asset<Tileset *> const *tileset) {
    this->tileSize = tileSize;
    this->tileset = tileset;
}

TileMap::~TileMap() {
    this->chunks.clear();
}

sf::Vector3i TileMap::getSize() const {
    // TODO: iterate over the chunks and find what the bounds are. Actually
    //       maybe just calculate this when the map is loaded in and save.
    //       Assuming this method is actually useful for something.
    return sf::Vector3i(0, 0, 0);
}

sf::Vector2u TileMap::getTileSize() const {
    return this->tileSize;
}

void TileMap::addChunk(sf::Vector2i offset, Chunk *chunk) {
    if (this->chunks.count(offset) > 0) {
        this->chunks[offset]->stack(chunk);
    } else {
        this->chunks[offset] = chunk;
    }
}
