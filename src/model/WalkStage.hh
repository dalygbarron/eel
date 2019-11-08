#ifndef WALK_STAGE_H
#define WALK_STAGE_H

#include "model/Asset.hh"
#include "model/Tileset.hh"
#include "model/Chunk.hh"
#include "model/Slice.hh"
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
        sf::Vector2u const chunkSize;
        sf::Vector2u const tileSize;

        /**
         * Default constructor which creates an empty stage.
         * @param bg        is the colour to draw behind the map.
         * @param tileset   is the tileset to draw the map with.
         * @param chunkSize is the width and breadth of each chunk.
         * @param tileSize  is the width and height of each tile as they
         *                  are spaced in the map (the pictures can be bigger
         *                  than this).
         */
        WalkStage(
            sf::Color bg,
            Asset<Tileset> const &tileset,
            sf::Vector2u chunkSize,
            sf::Vector2u tileSize
        );

        /**
         * Copy constructor which does a copy on a const so you will now have
         * one to play around with and change.
         * @param parent is the one that we are copying.
         */
        WalkStage(WalkStage const &parent);

        /**
         * Add a slice to the stage.
         * @param pos   is the 2d top down location of the slice.
         * @param slice is the slice to add.
         */
        void addSlice(sf::Vector2i pos, Slice const &slice);

        /**
         * Gives you all the slices in the given chunk.
         * @param pos is the location of the chunk.
         * @return a list of pointers to const slices. I know they are pointers
         *         but you have a personal promise from me that they will not
         *         be null.
         */
        std::vector<Slice const *> const &getSlices(sf::Vector2i pos) const;

    private:
        sf::Color bg;
        sf::RectangleShape shape;
        std::unordered_map<
            sf::Vector2i,
            Chunk,
            Utils::VectHash
        > chunks;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;
};

#endif
