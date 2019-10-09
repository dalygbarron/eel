#include "service/repository/TileMapRepository.hh"
#include "service/repository/TextRepository.hh"
#include "static/spdlog/spdlog.h"

TileMapRepository::TileMapRepository(
    char const *root,
    TilesetRepository *tilesetRepo
): Repository(root) {
    this->tilesetRepo = tilesetRepo;
}

TileMap *TileMapRepository::create(char const *filename, char const *key) {
    spdlog::info("creating tilemap: '{}'", filename);
    // Load main properties.
    sf::Vector2u tileSize;
    tileSize.x = node.attribute("tileWidth").asInt();
    tileSize.y = node.attribute("tileHeight").asInt();
    pugi::xml_node tileset = node.child("tileset");
    if (!tileset) {
        spdlog::error("Tilemap lacked tileset object");
        return 0;
    }
    Path tilesetFile(key, tileset.attribute("source").value());
    Asset<Tileset *> const tileset = tilesetRepo->get(tilesetFile.get());
    TileMap tileMap = new TileMap(tileSize, tileset);
    // Load layers.
    for (pugi::xml_node layer = node.child("layer"); layer;
        layer = layer.next_sibling("layer")) {
        spdlog::info(
            "Loading tilemap layer '{}'",
            layer.attribute("name").value()
        );
    }
    return tileMap;
}
