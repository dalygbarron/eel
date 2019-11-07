#include "model/Tileset.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <climits>

Tileset::Tileset(
    char const &name,
    sf::Vector2u tileSize,
    Asset<sf::Texture> const &texture
):
    name(&name),
    tileSize(tileSize),
    texture(texture)
{
    // hell yeah brother.
}
