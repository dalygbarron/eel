#include "service/repository/TileMapRepository.hh"
#include "service/repository/TextRepository.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Graphics.hpp>

TileMapRepository::TileMapRepository(
    char const *root,
    TextRepository *textRepo,
    TilesetRepository *tilesetRepo
): Repository(root) {
    this->textRepo = textRepo;
    this->tilesetRepo = tilesetRepo;
}

TileMap *TileMapRepository::create(
    char const *filename,
    char const *key
) const {
    spdlog::info("creating tilemap: '{}'", filename);
    pugi::xml_node node = this->textRepo->getXml(key, "map");
    // Load main properties.
    sf::Vector2u tileSize;
    tileSize.x = node.attribute("tileWidth").as_int();
    tileSize.y = node.attribute("tileHeight").as_int();
    sf::Color bg((node.attribute("backgroundcolor").as_int() << 8) | 0xff);
    pugi::xml_node tilesetNode = node.child("tileset");
    if (!tilesetNode) {
        spdlog::error("Tilemap lacked tileset object");
        return 0;
    }
    Path tilesetFile(key, tilesetNode.attribute("source").value());
    Asset<Tileset> const *tileset = tilesetRepo->get(tilesetFile.get());
    TileMap *tileMap = new TileMap(tileSize, tileset, bg);
    // Load layers.
    return tileMap;
    for (pugi::xml_node layer = node.child("layer"); layer;
        layer = layer.next_sibling("layer")
    ) {
        // TODO: finish
        spdlog::info(
            "Loading tilemap layer '{}'",
            layer.attribute("name").value()
        );
    }
    return tileMap;
}
