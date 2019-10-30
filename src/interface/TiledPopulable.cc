#include "interface/TiledPopulable.hh"
#include "static/Utils.hh"

void TiledPopulable::tiledPopulate(
    Repository<Tileset> const *tilesetRepo,
    const char *data
) {
    // Set up.
    pugi::xml_document doc;
    pugi::xml_node node;
    Utils::openXml(
        &doc,
        &node,
        "map",
        this->textRepo->get(key)->get()
    );
    // Load main map properties.
    sf::Vector2u size;
    sf::Vector2u tileSize;
    size.x = node.attribute("width").as_int();
    size.y = node.attribute("height").as_int();
    tileSize.x = node.attribute("tileWidth").as_int();
    tileSize.y = node.attribute("tileHeight").as_int();
    sf::Color bg((node.attribute("backgroundcolor").as_int() << 8) | 0xff);
    this->tiledMap(size, tileSize, bg);
    // Load tileset.
    pugi::xml_node tilesetNode = node.child("tileset");
    if (!tilesetNode) {
        spdlog::error("Tilemap lacked tileset object");
        return false;
    }
    Path tilesetFile(key, tilesetNode.attribute("source").value());
    Asset<Tileset> const *tileset = tilesetRepo->get(tilesetFile.get());
    this->tiledTileset(tileset);
    // Load Layers and chunks.
    // TODO: this.
    return true;
}
