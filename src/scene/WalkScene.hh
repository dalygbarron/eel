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
        constexpr static int MAX_MOBS = 10000;
        constexpr static int MAX_TILES = 7824;
        constexpr static int MAX_ACTORS = 64;
        constexpr static int MAX_BULLETS = 2048;
        constexpr static int MAX_PLACEMENTS = 64;
        constexpr static float MAP_CROSSING_BUFFER = 0.2;

        /**
         * Creates the scene.
         * @param engine is the engine stuff that the scene uses.
         * @param level  is the filename of the level.
         */
        WalkScene(Engine const *engine, char const *level);

        /**
         * Deletes all of this junk.
         */
        virtual ~WalkScene();

    private:

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
