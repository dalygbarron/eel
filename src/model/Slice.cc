#include "model/Slice.hh"

Slice::Slice(int height, sf::Vector2u size):
    height(height),
    size(size),
    data(new unsigned char[size.x * size.y])
{
    // bingo bongo.
}
