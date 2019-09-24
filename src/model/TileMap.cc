#include "model/TileMap.hh"
#include "service/Repository.hh"
#include "static/xml/pugixml.hpp"

TileMap::TileMap(char const *data, Repository *repository) {
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
    if (!map) {
        spdlog::critical("Tilemap object lacks top level map object");
        throw -1;
    }
    // Load main properties.
    this->dimensions.x = Utils::parseInt(map.attribute("width").value());
    this->dimensions.y = Utils::parseInt(map.attribute("height").value());
    this->tileSize.x = Utils::parseInt(map.attribute("tileWidth").value());
    this->tileSize.y = Utils::parseInt(map.attribute("tileHeight").value());
    this->orientation = TileMap::parseOrientation(
        map.attribute("orientation").value()
    );
    // Load tileset.
    pugi::xml_node tileset = tilemap.child("tileset");
    if (!tileset) {
        spdlog::critical("Tilemap lacked tileset object");
        throw -1;
    }
    char *tilesetSource = tileset.attribute("source").value();
    this->tileset = repository->getTileset(tilesetSource);
    // Load layers. All layers must have same size as level.
    tileset.select_nodes("layer").size();




}

TileMap::~TileMap() {
    delete this->tiles;
    delete this->regions;
}

unsigned char const *TileMap::getTiles() const {
    return this->tiles;
}

sf::Vector3i TileMap::getSize() const {
    return this->size;
}

sf::Vector2i TileMap::getTileSize() const {
    return this->tileSize;
}

static TileMap::Orientation TileMap::parseOrientation(
    char const *orientation
) {
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
