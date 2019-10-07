#ifndef ENGINE_H
#define ENGINE_H

#include "service/repository/TextRepository.hh"
#include "service/repository/TextureRepository.hh"
#include "service/repository/TilesetRepository.hh"
#include "service/repository/TileMapRepository.hh"
#include "service/repository/SoundRepository.hh"
#include "service/repository/MusicRepository.hh"
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
    TextRepository *textRepo;
    TextureRepository *textureRepo;
    TilesetRepository *tilesetRepo;
    TileMapRepository *tileMapRepo;
    SoundRepository *soundRepo;
    MusicRepository *musicRepo;
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
     * @param musicRepo      is the repo for music.
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
        MusicRepository *musicRepo,
        Radio *radio,
        Status *status,
        ControlBuilder const *controlBuilder
    );
};

#endif
