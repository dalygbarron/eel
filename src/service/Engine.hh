#ifndef ENGINE_H
#define ENGINE_H

#include "service/repository/TextRepository.hh"
#include "service/repository/TextureRepository.hh"
#include "service/repository/TilesetRepository.hh"
#include "service/repository/TileMapRepository.hh"
#include "service/repository/SoundRepository.hh"
#include "service/repository/RatPackRepository.hh"
#include "service/Config.hh"
#include "service/Radio.hh"
#include "service/Status.hh"
#include "service/builder/ControlBuilder.hh"

/**
 * Encapsulates gamewide services as needed by scenes.
 */
class Engine {
    public:
        Config const *config;
        TextRepository const *textRepo;
        TextureRepository const *textureRepo;
        TilesetRepository const *tilesetRepo;
        TileMapRepository const *tileMapRepo;
        SoundRepository const *soundRepo;
        RatPackRepository const *soundRepo;
        ControlBuilder const *controlBuilder;
        Radio *radio;
        Status *status;

        /**
         * Builds the engine and puts in all of it's dependencies in one swoop.
         * @param config         is the configuration.
         * @param textRepo       is the repo for text files.
         * @param textureRepo    is the repo for textures.
         * @param tilesetRepo    is the repo for tilesets.
         * @param tileMapRepo    is the repo for tile maps.
         * @param soundRepo      is the repo for sounds.
         * @param ratPackRepo    is the repo for spritesheets.
         * @param radio          is the audio controller.
         * @param status         is the game status.
         * @param controlBuilder is the control builder.
         * @param spritesheet    is the game's sprite sheet for sprites which
         *                       is not constant because it gets tilesets drawn
         *                       right onto it.
         */
        Engine(
            Config const *config,
            TextRepository const *textRepo,
            TextureRepository const *textureRepo,
            TilesetRepository const *tilesetRepo,
            TileMapRepository const *tileMapRepo,
            SoundRepository const *soundRepo,
            RatPackRepository const *ratPackRepo,
            Radio *radio,
            Status *status,
            ControlBuilder const *controlBuilder,
            sf::Texture *spritesheet
        );

        /**
         * Makes a spritesheet by joining the game's general spritesheet with
         * a given tileset picture.
         * @param space   is the sprite to cover with this texture.
         * @param tileset is the tileset to add to the spritesheet.
         * @return the spritesheet.
         */
        RatPack const *makeSpritesheet(
            char const *space,
            sf::Texture const *tileset
        ) const;

    private:
        RatPack *spriteSheet;
};

#endif
