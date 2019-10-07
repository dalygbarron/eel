#include "service/repository/TileMapRepository.hh"
#include "static/spdlog/spdlog.h"

TileMapRepository::TileMapRepository(TilesetRepository *tilesetRepo) {
    this->tilesetRepo = tilesetRepo;
}

TileMap *TileMapRepository::create(char const *filename) {
    spdlog::info("creating tilemap: '{}'", filename);
    // TODO: make the tilemap and all that.
    return 0;
}
