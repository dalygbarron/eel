#include "service/Engine.hh"
#include "static/Constant.hh"

Engine::Engine(
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
):
    root(&root),
    config(config),
    textRepo(textRepo),
    textureRepo(textureRepo),
    tilesetRepo(tilesetRepo),
    soundRepo(soundRepo),
    ratPackRepo(ratPackRepo),
    walkStageRepo(walkStageRepo),
    radio(radio),
    status(status),
    controlBuilder(controlBuilder),
    paneBuffer(paneBuffer)
{
    // does nothing else atm.
}

Repository<char> const &Engine::getTextRepository() const {
    return this->textRepo;
}

Repository<sf::Texture> const &Engine::getTextureRepository() const {
    return this->textureRepo;
}

Repository<Tileset> const &Engine::getTilesetRepository() const {
    return this->tilesetRepo;
}

Repository<sf::SoundBuffer> const &Engine::getSoundRepository() const {
    return this->soundRepo;
}

Repository<RatPack> const &Engine::getRatPackRepository() const {
    return this->ratPackRepo;
}

Repository<WalkStage> const &Engine::getWalkStageRepository() const {
    return this->walkStageRepo;
}

sf::FloatRect Engine::joinRatPack(
    char const &pack,
    char const &name,
    sf::Texture const &rat
) const {
    RatPack &ratPack = this->ratPackRepo.snatch(pack);
    sf::FloatRect size = ratPack.getRat(name);
    if (size.width == 0 || size.height == 0) {
        spdlog::error("Invalid rat name '{}' aborting join", &name);
        return size;
    }
    sf::Vector2u givenSize = rat.getSize();
    ratPack.getTextureMutable().update(rat, size.left, size.top);
    if (givenSize.x != size.left || givenSize.y != size.top) {
        spdlog::warn(
            "texture added to ratpack '{}' as rat '{}' but wrong size",
            &pack,
            &name
        );
    }
    return size;
}
