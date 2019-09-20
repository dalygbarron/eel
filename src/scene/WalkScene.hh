#ifndef WALK_SCENE_H
#define WALK_SCENE_H

#include "src/scene/Scene.hh"

/**
 * The main scene of the game where you walk around and shoot bullets and shit.
 */
class WalkScene: public Scene {
    public:
        constexpr static int MAX_MOBS = 10000;
        constexpr static int MAX_TILES = 7824;
        constexpr static int MAX_ACTORS = 64;
        constexpr static int MAX_ITEMS = 64;
        constexpr static int MAX_BULLETS = 2048;

        /**
         * Creates the scene.
         * @param level is the filename of the level.
         */
        WalkScene(char const *level);

        /**
         * Deletes all of this junk.
         */
        virtual ~WalkScene();

    private:
        Mob *mobs[WalkScene::MAX_MOBS];
        Tile *tiles[WalkScene::MAX_TILES];
        Actor *actors[WalkScene::MAX_ACTORS];
        Item *items[WalkScene::MAX_ITEMS];
        Bullet *bullets[WalkScene::MAX_BULLETS];
        int nTiles = 0;
        int nActors = 0;
        int nItems = 0;
        int nBullets = 0;
        sf::Vertex vertices[WalkScene::MAX_MOBS * 4];
        sf::VertexBuffer buffer;

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
        ) const;
};

#endif
