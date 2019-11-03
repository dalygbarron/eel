#ifndef WALK_STAGE_H
#define WALK_STAGE_H

#include "model/Asset.hh"
#include "model/Tileset.hh"
#include "static/Utils.hh"
#include <SFML/Graphics.hpp>
#include <unordered_map>

/**
 * Contains the goings on in a walk scene.
 */
class WalkStage: public sf::Drawable {
    public:
        constexpr static int MAX_MOBS = 4096;
        constexpr static int MAX_TILES = 2944;
        constexpr static int MAX_BULLETS = 1024;
        constexpr static int MAX_PLACEMENTS = 64;
        constexpr static int MAX_ACTORS = 64;

        Asset<Tileset> const &tileset;
        int const layers;
        sf::Vector2u const chunkDimensions;

        /**
         * Default constructor which creates an empty stage.
         * @param layers          is the number of layers in each chunk.
         * @param chunkDimensions is the width and breadth of each chunk.
         */
        WalkStage(
            sf::Color bg,
            Asset<Tileset> const &tileset,
            int layers,
            sf::Vector2u chunkDimensions
        );

        /**
         * Copy constructor which does a copy on a const so you will now have
         * one to play around with and change.
         * @param parent is the one that we are copying.
         */
        WalkStage(WalkStage const &parent);

        /**
         * Adds a chunk to the walk stage. It must be the same size as all
         * other chunks. Even if it does not have data for some layers it still
         * must include them just as blank.
         * @param pos   is the position that the chunk is at top down.
         * @param tiles is a pointer to the start of the chunk data.
         */
        void addChunk(sf::Vector2i pos, unsigned char &tiles);

    private:
        sf::Color bg;
        sf::RectangleShape shape;
        std::unordered_map<
            sf::Vector2i,
            unsigned char &,
            Utils::VectHash
        > chunks;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;
};

#endif
