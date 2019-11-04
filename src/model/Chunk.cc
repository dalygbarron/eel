#include "model/Chunk.hh"

Chunk::Chunk(sf::Vector2u size): size(size) {
    // greetings and welcome to Chunk.cc
}

std::vector<Slice const *> const &Chunk::getSlices() const {
    return this->slices;
}

void Chunk::addSlice(Slice const &slice) {
    this->slices.push_back(&slice);
}
