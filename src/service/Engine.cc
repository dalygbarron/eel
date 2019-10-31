#include "service/Engine.hh"
#include "static/Constant.hh"

Engine::Engine(
    Config const *config,
    Repository<char> *textRepo,
    Repository<sf::Texture> *textureRepo,
    Repository<Tileset> *tilesetRepo,
    Repository<sf::Sound> *soundRepo,
    Repository<RatPack> *ratPackRepo,
    Repository<WalkStage> *walkStageRepo,
    Radio *radio,
    Status *status,
    ControlBuilder const *controlBuilder
) {
    this->config = config;
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
    this->tilesetRepo = tilesetRepo;
    this->soundRepo = soundRepo;
    this->ratPackRepo = ratPackRepo;
    this->walkStageRepo = walkStageRepo;
    this->radio = radio;
    this->status = status;
    this->controlBuilder = controlBuilder;
}

Repository<char> const *Engine::getTextRepository() const {
    return this->textRepo;
}

Repository<sf::Texture> const *Engine::getTextureRepository() const {
    return this->textureRepo;
}

Repository<Tileset> const *Engine::getTilesetRepository() const {
    return this->tilesetRepo;
}

Repository<sf::Sound> const *Engine::getSoundRepository() const {
    return this->soundRepo;
}

Repository<RatPack> const *Engine::getRatPackRepository() const {
    return this->ratPackRepo;
}

Repository<WalkStage> const *Engine::getWalkStageRepository() const {
    return this->walkStage;
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
