#include "model/Tile.hh"

void Tile::restore(Tileset const &tileset, int id) {
    this->alive = true;
    // TODO: obviously tileset should know what the tile's height is.
    this->height = 1;
    if (this->pane) {
        this->pane->setPosition(sf::Vector2f(0, 0));
        this->pane->set(tileset.
    }
}
