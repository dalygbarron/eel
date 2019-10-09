#include "model/Chunk.hh"

Chunk::Chunk(sf::Vector2u dimensions, int z): dimensions(dimensions), z(z) {
    this->tiles = new unsigned char[dimensions.x * dimensions.y];
}

Chunk::~Chunk() {
    delete[] this->tiles;
}

void Chunk::stack(Chunk *chunk) {
    Chunk *top = this;
    while (top->next) top = top->next;
    top->next = chunk;
}
