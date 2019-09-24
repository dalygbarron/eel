#include "model/Tileset.hh"
#include "service/Repository.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/xml/pugixml.hpp"
#include <climits>

Tileset::Tileset(char const *data, Repository *repository) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(data);
    if (!result) {
        spdlog::critical(
            "Invalid XML in tileset file: {}",
            result.description()
        );
        throw -1;
    }
    pugi::xml_node tileset = doc.child("tileset");
    if (!tileset) {
        spdlog::critical("Tileset file lacks top level tileset object");
        throw -1;
    }
    // Load main properties.
    this->name = Utils::moveString(tileset.attribute("name").value());
    int tileCount = Utils::parseInt(tileset.attribute("tilecount").value());
    if (tileCount > UCHAR_MAX + 1) {
        spdlog::critical(
            "Tileset '{}' cannot be used as it has more than {} tiles",
            this->name,
            UCHAR_MAX + 1
        );
        delete this->name;
        throw -1;
    }
    int tileWidth = Utils::parseInt(tileset.attribute("tilewidth").value());
    int tileHeight = Utils::parseInt(tileset.attribute("tileheight").value());
    this->tileSize = sf::Vector2i(tileWidth, tileHeight);
    this->columns = Utils::parseInt(tileset.attribute("columns").value());
    // Load in the image and validate it.
    pugi::xml_node image = tileset.child("image");
    if (!image) {
        spdlog::critical(
            "Tileset '{}' has no image object in xml file",
            this->name
        );
        delete this->name;
        throw -1;
    }
    this->texture = repository->getTexture(image.attribute("source").value());
    // TODO: presumably tile properties are going to be stored in the tileset.
    //       need to load in the creator defined tiled height which will default
    //       to 0. Maybe other custom properties as well, I do not know.
}

Tileset::~Tileset() {
    delete this->name;
}

char const *Tileset::getName() const {
    return this->name;
}

sf::Vector2i Tileset::getTileSize() const {
    return this->tileSize;
}

void Tileset::buildQuad(sf::Vertex *vertices, unsigned char id) const {

}

void Tileset::apply(sf::Texture *atlas) const {
    sf::Vector2u size = this->texture->getSize();
    if (size.x > Constant::TILESET_MAX_WIDTH ||
        size.y > Constant::TILESET_MAX_HEIGHT) {
        spdlog::warn(
            "Tileset '{}' must fit ({}, {}) for texture atlas. is ({}, {})",
            this->name,
            Constant::TILESET_MAX_WIDTH,
            Constant::TILESET_MAX_HEIGHT,
            size.x,
            size.y
        );
        return;
    }
    atlas->update(*(this->texture));
}
