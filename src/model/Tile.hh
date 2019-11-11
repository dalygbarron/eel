#ifndef TILE_H
#define TILE_H

#include "model/Mob.hh"
#include "model/Tileset.hh"

/**
 * Represents a single piece of the terra firma in 3d space. Mostly just makes
 * reference to a kind of tile but can also be specially chosen to have an
 * effect which is basically just a thingo to make it transfer you to
 * a different scene.
 */
class Tile: public Mob {
    public:
        unsigned char value;
        char *effect;
        int height;

        /**
         * Turns this tile into a new tile with the given id from the given
         * tileset.
         * @param tileset is the tileset the tile belongs to.
         * @param id      is the id number of the tile to create.
         */
        void restore(Tileset const &tileset, int id);
};

#endif
