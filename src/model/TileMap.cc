#include "model/TileMap.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include "static/xml/pugixml.hpp"
#include <string.h>

TileMap::TileMap(pugi::xml_node node, TilesetRepository *tilesetRepo) {
    // Load main properties.
    this->tileSize.x = Utils::parseInt(node.attribute("tileWidth").value());
    this->tileSize.y = Utils::parseInt(
        node.attribute("tileHeight").value()
    );
    this->orientation = TileMap::parseOrientation(
        node.attribute("orientation").value()
    );
    // Load tileset.
    pugi::xml_node tileset = node.child("tileset");
    if (!tileset) {
        spdlog::critical("Tilemap lacked tileset object");
        throw -1;
    }
    char const *tilesetSource = tileset.attribute("source").value();
    this->tileset = tilesetRepo->get(tilesetSource);
    // Load layers.
    for (pugi::xml_node layer = node.child("layer"); layer;
        layer = layer.next_sibling("layer")) {
        spdlog::info(
            "Loading tilemap layer '{}'",
            layer.attribute("name").value()
        );
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
