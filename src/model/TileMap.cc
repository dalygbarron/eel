#include "model/TileMap.hh"
#include "service/Repository.hh"
#include "static/Utils.hh"
#include "static/xml/pugixml.hpp"

TileMap::TileMap(char const *data, Repository *repository) {
    spdlog::info("Loading tilemap");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(data);
    if (!result) {
        spdlog::critical(
            "Invalid XML in tilemap file: {}",
            result.description()
        );
        throw -1;
    }
    pugi::xml_node tilemap = doc.child("map");
    if (!tilemap) {
        spdlog::critical("Tilemap object lacks top level map object");
        throw -1;
    }
    // Load main properties.
    this->tileSize.x = Utils::parseInt(tilemap.attribute("tileWidth").value());
    this->tileSize.y = Utils::parseInt(
        tilemap.attribute("tileHeight").value()
    );
    this->orientation = TileMap::parseOrientation(
        tilemap.attribute("orientation").value()
    );
    // Load tileset.
    pugi::xml_node tileset = data.child("tileset");
    if (!tileset) {
        spdlog::critical("Tilemap lacked tileset object");
        throw -1;
    }
    char const *tilesetSource = tileset.attribute("source").value();
    this->tileset = repository->getTileset(tilesetSource);
    // Load layers.
    for (pugi::xml_node layer = tilemap.child("layer"); layer;
        layer = layer.next_sibling("layer")) {
        spdlog::info(
            "Loading tilemap layer '{}'",
            layer.attribute("name").value()
        );
        spdlog::info(data.value());
    }
}

TileMap::~TileMap() {
    this->chunks.clear();
    delete this->regions;
}

sf::Vector3i TileMap::getSize() const {
    // TODO: iterate over the chunks and find what the bounds are. Actually
    //       maybe just calculate this when the map is loaded in and save.
    //       Assuming this method is actually useful for something.
}

sf::Vector2u TileMap::getTileSize() const {
    return this->tileSize;
}

TileMap::Orientation TileMap::parseOrientation(char const *orientation) {
    if (strcmp(orientation, "orthagonal") == 0) {
        return TileMap::Orientation::ORTHAGONAL;
    } else if (strcmp(orientation, "isometric") == 0) {
        return TileMap::Orientation::ISOMETRIC;
    } else {
        spdlog::warn(
            "Can't parse invalid orientation '{}', defaulting to isometric",
            orientation
        );
        return TileMap::Orientation::ISOMETRIC;
    }
}
