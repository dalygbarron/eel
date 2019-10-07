#ifndef ENGINE_H
#define ENGINE_H

#include "service/Config.hh"
#include "service/Radio.hh"
#include "service/Status.hh"
#include "service/builder/ControlBuilder.hh"

/**
 * Encapsulates gamewide services as needed by scenes.
 */
class Engine {
public:
    // General services.
    Config const *config;
    ControlBuilder const *controlBuilder;
    Radio *radio;
    Status *status;
    // Repositories.
    TextRepository *textRepo;
    TextureRepository *textureRepo;
    TilesetRepository *tilesetRepo;
    TileMapRepository *tileMapRepo;
    SoundRepository *soundRepo;
    MusicRepository *musicRepo;

    /**
     * Builds the engine and puts in all of it's dependencies in one swoop.
     * @param config         is the configuration.
     * @param radio          is the audio controller.
     * @param status         is the game status.
     * @param repository     is the asset repositoey.
     * @param controlBuilder is the control builder.
     * @param textRepo       is the repo for text files.
     * @param textureRepo    is the repo for textures.
     * @param tilesetRepo    is the repo for tilesets.
     * @param tileMapRepo    is the repo for tile maps.
     * @param soundRepo      is the repo for sounds.
     * @param musicRepo      is the repo for music.
     */
    Engine(
        Config const *config,
        Radio *radio,
        Status *status,
        Repository *repository,
        ControlBuilder const *controlBuilder,
        TextRepository *textRepo,
        TextureRepository *textureRepo,
        TilesetRepository *tilesetRepo,
        TileMapRepository *tileMapRepo,
        SoundRepository *soundRepo,
        MusicRepository *musicRepo
    );
};

#endif
