#include "model/TileChunk.hh"
#include "static/Utils.hh"

TileChunk::TileChunk(pugi::xml_node node) {
    this->size.x = node->attribute("width")->valueAsInt();
    this->size.y = node->attribute("width")->valueAsInt();
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

sf::Vector2i TileChunk::getSize() const {
    return this->size;
}

sf::Vector2i TileChunk::getOffset() const {
    return this->offset;
}
