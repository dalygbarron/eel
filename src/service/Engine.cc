#include "service/Engine.hh"
#include "static/Constant.hh"

Engine::Engine(
    Config const *config,
    TextRepository const *textRepo,
    TextureRepository const *textureRepo,
    TilesetRepository const *tilesetRepo,
    TileMapRepository const *tileMapRepo,
    SoundRepository const *soundRepo,
    Radio *radio,
    Status *status,
    ControlBuilder const *controlBuilder,
    sf::Texture *spritesheet
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
    this->spritesheet = spritesheet;
}

sf::Texture const *Engine::makeSpritesheet(sf::Texture const *tileset) const {
    sf::Vector2u size = tileset->getSize();
    if (size.x > Constant::TILESET_MAX_WIDTH ||
        size.y > Constant::TILESET_MAX_HEIGHT) {
        spdlog::warn(
            "Tileset must fit ({}, {}) for texture atlas. is ({}, {})",
            Constant::TILESET_MAX_WIDTH,
            Constant::TILESET_MAX_HEIGHT,
            size.x,
            size.y
        );
        return 0;
    }
    this->spritesheet->update(*(tileset));
    return this->spritesheet;
}
