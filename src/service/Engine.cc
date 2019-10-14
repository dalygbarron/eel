#include "service/Engine.hh"

Engine::Engine(
    Config const *config,
    TextRepository *textRepo,
    TextureRepository *textureRepo,
    TilesetRepository *tilesetRepo,
    TileMapRepository *tileMapRepo,
    SoundRepository *soundRepo,
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
    this->radio = radio;
    this->status = status;
    this->controlBuilder = controlBuilder;
}
