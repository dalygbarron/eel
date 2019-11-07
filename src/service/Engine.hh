#ifndef ENGINE_H
#define ENGINE_H

#include "model/Tileset.hh"
#include "model/RatPack.hh"
#include "model/WalkStage.hh"
#include "service/repository/Repository.hh"
#include "service/Config.hh"
#include "service/Radio.hh"
#include "service/Status.hh"
#include "service/PaneBuffer.hh"
#include "service/builder/ControlBuilder.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

/**
 * Encapsulates gamewide services as needed by scenes.
 */
class Engine {
    public:
        std::string const root;
        Config const &config;
        ControlBuilder const &controlBuilder;
        Radio &radio;
        Status &status;
        PaneBuffer &paneBuffer;

        /**
         * Builds the engine and puts in all of it's dependencies in one swoop.
         * @param root           is the root directory of the game.
         * @param config         is the configuration.
         * @param textRepo       is the repo for text files.
         * @param textureRepo    is the repo for textures.
         * @param tilesetRepo    is the repo for tilesets.
         * @param soundRepo      is the repo for sounds.
         * @param ratPackRepo    is the repo for spritesheets.
         * @param walkStageRepo  is the repo for walk stages.
         * @param radio          is the audio controller.
         * @param status         is the game status.
         * @param controlBuilder is the control builder.
         * @param paneBuffer     is the pane buffer for drawing quads.
         */
        Engine(
            char const &root,
            Config const &config,
            Repository<char> &textRepo,
            Repository<sf::Texture> &textureRepo,
            Repository<Tileset> &tilesetRepo,
            Repository<sf::SoundBuffer> &soundRepo,
            Repository<RatPack> &ratPackRepo,
            Repository<WalkStage> &walkStageRepo,
            Radio &radio,
            Status &status,
            ControlBuilder const &controlBuilder,
            PaneBuffer &paneBuffer
        );

        /**
         * Gets the engine's text repository instance.
         * @return the text repository.
         */
        Repository<char> const &getTextRepository() const;

        /**
         * Gets the engine's texture repository instance.
         * @return the texture repository.
         */
        Repository<sf::Texture> const &getTextureRepository() const;

        /**
         * Gets the engine's tileset repo instance.
         * @return the tileset repo.
         */
        Repository<Tileset> const &getTilesetRepository() const;

        /**
         * Gets the engine's sound repo instance.
         * @return the sound repo.
         */
        Repository<sf::SoundBuffer> const &getSoundRepository() const;

        /**
         * Gets the engine's rat pack repo instance.
         * @return the ratpack repo.
         */
        Repository<RatPack> const &getRatPackRepository() const;

        /**
         * Gets the engine's walk stage repo instance.
         * @return the walk stage repo.
         */
        Repository<WalkStage> const &getWalkStageRepository() const;

        /**
         * Draws a texture onto a given ratpack object.
         * @param pack    is the key to the ratpack to edit.
         * @param name    is the name of the rat in the pack to draw over.
         * @param texture is the texture to draw over it with.
         */
        void joinRatPack(
            char const &pack,
            char const &name,
            sf::Texture const &rat
        ) const;

    private:
        Repository<char> &textRepo;
        Repository<sf::Texture> &textureRepo;
        Repository<Tileset> &tilesetRepo;
        Repository<sf::SoundBuffer> &soundRepo;
        Repository<RatPack> &ratPackRepo;
        Repository<WalkStage> &walkStageRepo;
};

#endif
