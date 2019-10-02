#include "model/TileChunk.hh"
#include "static/Utils.hh"

TileChunk::TileChunk(pugi::xml_node node) {
    this->offset.x = node->attribute("x")->asInt();
    this->offset.y node->attribute("y")->asInt();
    this->size.x = node->attribute("width")->asInt();
    this->size.y = node->attribute("width")->asInt();
    int length = this->size.x * this->sizey;
    this->tiles = new unsigned char[length];
    int n = Utils::parseBase64(node->value(), this->tiles);
    if (n != length) {
        spdlog::warn("Tilechunk data less than expected");
    }
    for (int i = 0; i < n; i++) {
        spdlog::info(this->tiles[i]);
    }
}

TileChunk::~TileChunk() {
    delete this->tiles;
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
