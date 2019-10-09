#include "service/repository/TileMapRepository.hh"
#include "static/spdlog/spdlog.h"

TileMapRepository::TileMapRepository(
    char const *root,
    TilesetRepository *tilesetRepo
): Repository(root) {
    this->tilesetRepo = tilesetRepo;
}

TileMap *TileMapRepository::create(char const *filename) {
    spdlog::info("creating tilemap: '{}'", filename);
    return new TileMap(node, this->tilesetRepository);
}
