#include "model/Tileset.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <climits>

Tileset::Tileset(
    char const &name,
    sf::Vector2u tileSize,
    sf::FloatRect bounds
    Asset<sf::Texture> const &texture
):
    name(&name),
    tileSize(tileSize),
    bounds(bounds),
    texture(texture)
{
    // hell yeah brother.
}

void Tileset::buildQuad(sf::Vertex &vertices, unsigned char id) const {
    int x = id % (this->bounds.w / this->tileSize.x);
    int y = id / (this->bounds.w / this->tileSize.x);


}
