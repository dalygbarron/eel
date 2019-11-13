#include "model/Tile.hh"

void Tile::restore(Tileset const &tileset, int id) {
    this->alive = true;
    // TODO: obviously tileset should know what the tile's height is.
    this->height = 1;
    if (this->pane) {
        tileset.fitPane(*this->pane, id);
    }
}
