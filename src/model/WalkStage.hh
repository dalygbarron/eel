#ifndef WALK_STAGE_H
#define WALK_STAGE_H

#include "interface/TiledPopulable.hh"
#include <SFML/Graphics.hpp>

/**
 * Contains the goings on in a walk scene.
 */
class WalkStage: public TiledPopulable, public sf::Drawable {
    public:
        constexpr static int MAX_MOBS = 4096;
        constexpr static int MAX_TILES = 2944;
        constexpr static int MAX_BULLETS = 1024;
        constexpr static int MAX_PLACEMENTS = 64;
        constexpr static int MAX_ACTORS = 64;

        /**
         * Default constructor which creates an empty stage.
         */
        WalkStage();

        /**
         * Copy constructor which does a copy on a const so you will now have
         * one to play around with and change.
         * @param parent is the one that we are copying.
         */
        WalkStage(WalkStage const *parent);

        /**
         * Gives you the walkstage's tileset if it has got one set.
         * @return the tileset as an asset pointer if there is one or null if
         *         it doesn't have a tileset yet.
         */
        Asset<Tileset> const *getTileset() const;

    private:
        sf::Color bg;
        Asset<Tileset> const *tileset;

        virtual void tiledMap(
            sf::Vector2u size,
            sf::Vector2u tileSize,
            sf::Color bg
        ) override;

        virtual void tiledTileset(Asset<Tileset> const *tileset) override;

        virtual void tiledLayer() override;

        virtual void tiledChunk() override;

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;

};

#endif
