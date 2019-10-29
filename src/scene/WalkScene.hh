#ifndef WALK_SCENE_H
#define WALK_SCENE_H

#include "scene/Scene.hh"
#include "service/Engine.hh"
#include "model/Mob.hh"
#include "model/Actor.hh"
#include "model/Bullet.hh"
#include "model/Placement.hh"
#include "model/Tile.hh"
#include "model/TileMap.hh"

/**
 * The main scene of the game where you walk around and shoot bullets and shit.
 */
class WalkScene: public Scene {
    public:
        /**
         * Creates the scene.
         * @param engine is the engine stuff that the scene uses.
         * @param map    is the map that should be put into the scene.
         */
        WalkScene(Engine const *engine, Asset<TileMap> const *map);

        /**
         * Deletes all of this junk.
         */
        virtual ~WalkScene();

        /**
         * Updates all of the things in the stage like items and actors etc.
         * @param engine provides access to input and other stuff.
         * @param delta  is the time passed since the last frame.
         */
        virtual void logic(float delta);

        /**
         * Renders the stage.
         * @param target is the screen to render to.
         * @param states are the rendering states used to modify how it's
         *               rendered and all that.
         */
        virtual void render(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const;

        /**
         * moves the focus of the stage which controls where the camera shows.
         * Also if the focus moves too far over the borders of chunks then the
         * currently displayed chunks will be changed.
         * @param newFocus is the place that should be the new centre of
         *                 attention in pixels not tiles.
         */
        void refocus(sf::Vector2f newFocus);

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
        sf::Vector2f focus;
        sf::Vector2i focusChunk;
        Asset<RatPack> const *sprites;
        sf::Sprite background;

        /**
         * Sorts all the scene's mobs and gives the range that changed.
         * @return a vector where x is the lowest index of a mob that changed,
         *         and y is the highest index.
         */
        sf::Vector2i sortMobs();

        virtual void logic(float delta) override;

        virtual void render(
            sf::RenderTarget *target,
            sf::RenderStates states
        ) const override;
};

#endif
