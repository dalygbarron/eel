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
         * Creates the walk stage by giving it the map.
         * @param map is the map the stage will use.
         */
        WalkStage(TileMap const *map);

        /**
         * Deletes the stage's mobs and crap.
         */
        ~WalkStage();

        /**
         * moves the focus of the stage which controls where the camera shows.
         * Also if the focus moves too far over the borders of chunks then the
         * currently displayed chunks will be changed.
         * @param newFocus is the place that should be the new centre of
         *                 attention in pixels not tiles.
         */
        void refocus(sf::Vector2f newFocus);

        /**
         * Updates all of the things in the stage like items and actors etc.
         * @param engine provides access to input and other stuff.
         * @param delta  is the time passed since the last frame.
         */
        void update(Engine *engine, float delta);

        /**
         * Renders the stage.
         * @param target is the screen to render to.
         * @param states are the rendering states used to modify how it's
         *               rendered and all that.
         */
        void render(sf::RenderTarget &target, sf::RenderStates states);

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
        sf::Vector2f focus;
        sf::Vector2i focusChunk;
};

#endif
