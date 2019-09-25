#ifndef WALK_STAGE_H
#define WALK_STAGE_H

#include "model/Mob.hh"
#include "model/Tile.hh"
#include "model/Actor.hh"
#include "model/Placement.hh"
#include "model/Bullet.hh"
#include "model/TileMap.hh"
#include "model/Tileset.hh"

/**
 * Represents a little world where things move around in isometric 3d. It can
 * consist of many different tile maps which get grafted together as the focus
 * moves.
 */
class WalkStage {
    public:
        /**
         * Creates the walk stage by giving it the first map it will enjoy.
         * @param start is the first map.
         */
        WalkStage(TileMap const *start);

        /**
         * Deletes the stage's mobs and crap.
         */
        ~WalkStage();

        /**
         * Adds the tiles of several chunks into the level, overwriting ones
         * that are no longer in focus.
         * @param a is the first chunk.
         * @param b is the second chunk.
         * @param c is the third chunk.
         */
        void addThreeChunks(
            TileChunk const *a,
            TileChunk const *b,
            TileChunk const *c
        );

        /**
         * Adds the tiles of several chunks into the level, overwriting ones
         * that are no longer in focus.
         * @param a is the first chunk.
         * @param b is the second chunk.
         * @param c is the third chunk.
         * @param d is the fourth chunk.
         * @param e is the fifth chunk.
         */
        void addFiveChunks(
            TileChunk const *a,
            TileChunk const *b,
            TileChunk const *c,
            TileChunk const *d,
            TileChunk const *e
        );

    private:
        Mob *mobs[WalkScene::MAX_MOBS];
        Tile *tiles[WalkScene::MAX_TILES];
        Actor *actors[WalkScene::MAX_ACTORS];
        Placement *placements[WalkScene::MAX_PLACEMENTS];
        Bullet *bullets[WalkScene::MAX_BULLETS];
        int nTiles = 0;
        int nActors = 0;
        int nPlacements = 0;
        int nBullets = 0;
        sf::Vertex vertices[WalkScene::MAX_MOBS * 4];
        sf::VertexBuffer buffer;
        TileMap const *map;
        sf::Vector2i sector;
        sf::Vector2i mapSize;
};

#endif
