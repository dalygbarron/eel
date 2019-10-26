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
    sf::Texture const *rat
) const {
    RatPack *ratPack = this->ratPackRepo->snatch(pack);
    sf::IntRect size = ratPack->getRat(name);
    sf::Vector2u givenSize = rat->getSize();
    ratPack->getTextureMutable()->update(*rat, size.left, size.top);
    if (givenSize.x != size.left || givenSize.y != size.top) {
        spdlog::warn(
            "texture added to ratpack '{}' as rat '{}' but wrong size",
            pack,
            name
        );
    }
}
