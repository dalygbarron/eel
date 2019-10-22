#include "service/Engine.hh"
#include "static/Constant.hh"

Engine::Engine(
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
) {
    this->config = config;
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
    this->tilesetRepo = tilesetRepo;
    this->tileMapRepo = tileMapRepo;
    this->soundRepo = soundRepo;
    this->ratPackRepo = ratPackRepo;
    this->radio = radio;
    this->status = status;
    this->controlBuilder = controlBuilder;
}

TextRepository const *Engine::getTextRepository() const {
    return this->textRepo;
}

TextureRepository const *Engine::getTextureRepository() const {
    return this->textureRepo;
}

TilesetRepository const *Engine::getTilesetRepository() const {
    return this->tilesetRepo;
}

TileMapRepository const *Engine::getTileMapRepository() const {
    return this->tileMapRepo;
}

SoundRepository const *Engine::getSoundRepository() const {
    return this->soundRepo;
}

RatPackRepository const *Engine::getRatPackRepository() const {
    return this->ratPackRepo;
}

void Engine::joinRatPack(
    char const *pack,
    char const *name,
    char const *texture
) {
    RatPack *ratpack = this->ratPackRepo->snatch(pack);
    sf::Texture *rat = this->textureRepo->get(texture)->get();
    ratPack

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
