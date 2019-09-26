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
    this->size.x = Utils::parseInt(tilemap.attribute("width").value());
    this->size.y = Utils::parseInt(tilemap.attribute("height").value());
    this->tileSize.x = Utils::parseInt(tilemap.attribute("tileWidth").value());
    this->tileSize.y = Utils::parseInt(
        tilemap.attribute("tileHeight").value()
    );
    this->orientation = TileMap::parseOrientation(
        tilemap.attribute("orientation").value()
    );
    // Load tileset.
    pugi::xml_node tileset = tilemap.child("tileset");
    if (!tileset) {
        spdlog::critical("Tilemap lacked tileset object");
        throw -1;
    }
    char const *tilesetSource = tileset.attribute("source").value();
    this->tileset = repository->getTileset(tilesetSource);
    // Load layers. All layers must have same size as level.
    this->size.z = tileset.select_nodes("layer").size();
    if (this->size.z == 0) spdlog::warn("map has no layers");
    this->tiles = new unsigned char[
        this->size.x * this->size.y * this->size.z
    ];
    for (pugi::xml_node layer = tilemap.child("layer"); layer;
        layer = layer.next_sibling("layer")) {
        spdlog::info(
            "Loading tilemap layer '{}'",
            layer.attribute("name").value()
        );
        int width = Utils::parseInt(layer.attribute("width").value());
        int height = Utils::parseInt(layer.attribute("height").value());
        if (this->size.x != width || this->size.y != height) {
            spdlog::critical(
                "Layer '{}' has different size to map",
                layer.attribute("name").value()
            );
            delete this->tiles;
            throw -1;
        }
        pugi::xml_node data = layer.child("data");
        if (!data) {
            spdlog::warn(
                "Layer '{}' has no data",
                layer.attribute("name").value()
            );
            continue;
        }
        spdlog::info(data.value());
        // TODO: this is the part where we iterate over the data. This should
        //       possibly be moved out to a function. Also I think tiled has
        //       multiple methods of storing the data so possibly I will want
        //       to handle all of them though that seems like a bit of a waste
        //       of time.
        //       It would at least be good to be able to say I handle one of
        //       them and reject the others.
    }
}

TileMap::~TileMap() {
    delete this->chunks;
    delete this->regions;
}

unsigned char const *TileMap::getTiles() const {
    return this->tiles;
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
