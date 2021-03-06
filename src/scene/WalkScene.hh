#ifndef WALK_SCENE_H
#define WALK_SCENE_H

#include "scene/Scene.hh"
#include "service/Engine.hh"
#include "model/Mob.hh"
#include "model/Actor.hh"
#include "model/Bullet.hh"
#include "model/Placement.hh"
#include "model/Tile.hh"

/**
 * The main scene of the game where you walk around and shoot bullets and shit.
 */
class WalkScene: public Scene {
    public:
        /**
         * Creates the scene.
         * @param engine    is the engine stuff that the scene uses.
         * @param prototype is the map that should be put into the scene.
         */
        WalkScene(Engine const &engine, WalkStage const &prototype);

        /**
         * Deletes all of this junk.
         */
        virtual ~WalkScene();

    private:
        sf::Vector2f camera;
        WalkStage stage;
        Actor *player;

        virtual void logic(float delta, sf::View &view) override;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;
};

#endif
