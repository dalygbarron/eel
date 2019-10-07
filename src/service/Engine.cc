#include "service/Engine.hh"

Engine::Engine(
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
) {
    this->config = config;
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
    this->tilesetRepo = tilesetRepo;
    this->tileMapRepo = tileMapRepo;
    this->soundRepo = soundRepo;
    this->musicRepo = musicRepo;
    this->radio = radio;
    this->status = status;
    this->controlBuilder = controlBuilder;
}
