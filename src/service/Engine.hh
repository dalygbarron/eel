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
         */
        Engine(
            Config const *config,
            TextRepository *textRepo,
            TextureRepository *textureRepo,
            TilesetRepository *tilesetRepo,
            TileMapRepository *tileMapRepo,
            SoundRepository *soundRepo,
            RatPackRepository *ratPackRepo,
            Radio *radio,
            Status *status,
            ControlBuilder const *controlBuilder
        );

        /**
         * Gets the engine's text repository instance.
         * @return the text repository.
         */
        TextRepository const *getTextRepository();

        /**
         * Gets the engine's texture repository instance.
         * @return the texture repository.
         */
        TextureRepository const *getTextureRepository();

        /**
         * Gets the engine's tileset repo instance.
         * @return the tileset repo.
         */
        TilesetRepository const *getTilesetRepository();

        /**
         * Gets the engine's tilemap repo instance.
         * @return the tilemap repo.
         */
        TileMapRepository const *getTileMapRepository();

        /**
         * Gets the engine's sound repo instance.
         * @return the sound repo.
         */
        SoundRepository const *getSoundRepository();

        /**
         * Gets the engine's rat pack repo instance.
         * @return the ratpack repo.
         */
        RatPackRepository const *getRatPackRepository();

        /**
         * Draws a texture onto a given ratpack object.
         * @param pack    is the key to the ratpack to edit.
         * @param name    is the name of the rat in the pack to draw over.
         * @param texture is the texture to draw over it with.
         */
        void joinRatPack(
            char const *pack,
            char const *name,
            char const *texture
        ) const;

    private:
        TextRepository *textRepo;
        TextureRepository *textureRepo;
        TilesetRepository *tilesetRepo;
        TileMapRepository *tileMapRepo;
        SoundRepository *soundRepo;
        RatPackRepository *ratPackRepo;
};

#endif
