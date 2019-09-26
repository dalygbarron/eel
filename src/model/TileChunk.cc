#include "model/TileChunk.hh"

TileChunk::TileChunk(sf::Vector3i size, sf::Vector2i offset) {
    this->size = size;
    this->offset = offset;
    this->tiles = new unsigned char[size.x * size.y * size.z];
}

TileChunk::~TileChunk() {
    delete this->tiles;
}

void TileChunk::setTile(sf::Vector3i pos, unsigned char value) {
    int index = pos.x % size.x + pos.y * size.x + pos.z * size.x * size.y;
    this->tiles[index] = value;
}

unsigned char const *TileChunk::getTiles() {
    return this->tiles;
}
