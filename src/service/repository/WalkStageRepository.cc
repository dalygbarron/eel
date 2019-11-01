#include "service/repository/WalkStageRepository.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Graphics.hpp>

WalkStageRepository::WalkStageRepository(
    char const *root,
    Repository<char> const *textRepo,
    Repository<Tileset> const *tilesetRepo
): Repository(root) {
    this->textRepo = textRepo;
    this->tilesetRepo = tilesetRepo;
}

WalkStage *WalkStageRepository::create(
    char const *filename,
    char const *key
) const {
    spdlog::info("creating walkstage: '{}'", filename);
    WalkStage *walkStage = new WalkStage();
    char const *data = this->textRepo->get(key)->get();
    walkStage->tiledPopulate(this->tilesetRepo, key, data);
    return walkStage;
}
