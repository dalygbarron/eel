#include "service/Engine.hh"

Engine::Engine(
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
) {
    this->config = config;
    this->radio = radio;
    this->status = status;
    this->repository = repository;
    this->controlBuilder = controlBuilder;
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
    this->tilesetRepo = tilesetRepo;
    this->tileMapRepo = tileMapRepo;
    this->soundRepo = soundRepo;
    this->musicRepo = musicRepo;
}
