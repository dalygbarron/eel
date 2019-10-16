#include "service/repository/TilesetRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"

TilesetRepository::TilesetRepository(
    char const *root,
    TextRepository *textRepo,
    TextureRepository *textureRepo
): Repository(root) {
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
}

Tileset *TilesetRepository::create(
    char const *filename,
    char const *key
) const {
    spdlog::info("creating tileset: '{}'", filename);
    pugi::xml_node node = this->textRepo->getXml(key, "tileset");
    char const *name = Utils::moveString(node.attribute("name").value());
    sf::Vector2u tileSize;
    tileSize.x = node.attribute("tileWidth").as_int();
    tileSize.y = node.attribute("tileHeight").as_int();
    pugi::xml_node imageNode = node.child("image");
    Path imagePath(key, imageNode.attribute("source").value());
    Tileset *tileset = new Tileset(
        name,
        tileSize,
        this->textureRepo->get(imagePath.get())
    );
    return tileset;
}
