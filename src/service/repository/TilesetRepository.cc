#include "service/repository/TilesetRepository.hh"
#include "static/spdlog/spdlog.h"

TilesetRepository::TilesetRepository(
    char const *root,
    TextRepository *textRepo,
    TextureRepository *textureRepo
): Repository(root) {
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
}

Tileset *TilesetRepository::create(char const *filename) {
    spdlog::info("creating tileset: '{}'", filename);
    // TODO: this is meant to go through some xml loading function.
    pugi::xml_document  doc;
    char const *data = this->textRepo->get(filename)->content;
    Tileset *tileset = new Tileset(doc, this->textureRepo);
    return tileset;
}
