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

void Tileset::fitPane(Pane &pane, int id) const {
    if (pane.vertices) {
        sf::Texture const &actualTexture = this->texture.get();
        sf::Vector2u textureSize = actualTexture.getSize();
        int x = (id - 1) % textureSize.x;
        int y = (id - 1) / textureSize.y;
        pane.vertices[0].position = sf::Vector2f(0 - this->tileSize.x / 2, 0 - this->tileSize.y / 2);
        pane.vertices[1].position = sf::Vector2f(this->tileSize.x / 2, 0 - this->tileSize.y / 2);
        pane.vertices[2].position = sf::Vector2f(this->tileSize.x / 2, this->tileSize.y / 2);
        pane.vertices[3].position = sf::Vector2f(0 - this->tileSize.x / 2, this->tileSize.y / 2);
        pane.vertices[0].texCoords = sf::Vector2f(x * this->tileSize.x, y * this->tileSize.y);
        pane.vertices[1].texCoords = sf::Vector2f((x + 1) * this->tileSize.x, y * this->tileSize.y);
        pane.vertices[2].texCoords = sf::Vector2f((x + 1) * this->tileSize.x, (y + 1) * this->tileSize.y);
        pane.vertices[3].texCoords = sf::Vector2f(x * this->tileSize.x, (y + 1) * this->tileSize.y);
    }
}
