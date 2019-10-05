#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include "service/Repository.hh"
#include "service/Config.hh"

// TODO: I forgot now damn it. uhhhhhh.
//       Oh yeah, these catches will catch exceptions thrown by me with the
//       intention of stopping the program. I need to make the exception
//       catching actually catch the exception I am looking for.

Repository::Repository(Config const *config) {
    this->path.apply(config->getRoot());
    char const *fontFile = config->get("font");
    this->path.applyFolders(fontFile);
    if (!this->font.loadFromFile(this->path.in(fontFile))) {
        spdlog::critical("Could not load font from file '{}'", fontFile);
        throw -1;
    }
    this->path.removeFolders(fontFile);
}

Repository::~Repository() {
    this->textures.clear();
    this->texts.clear();
    // TODO: and the rest.
}

sf::Texture *Repository::getTexture(char const *name) {
    spdlog::info("get texture: '{}'", name);
    try {
        return this->textures.at(name);
    } catch (...) {
        sf::Texture *texture = new sf::Texture();
        this->path.applyFolders(name);
        if (!texture->loadFromFile(this->path.in(name))) {
            spdlog::critical(
                "Cannot load texture at '{}'",
                this->path.render()
            );
            throw -1;
        } else {
            this->path.removeFolders(name);
            texture->setSmooth(true);
            texture->setRepeated(true);
            this->textures[name] = texture;
            return texture;
        }
    }
}

SpriteBatch *Repository::getSpriteBatch(char const *name) {
    spdlog::info("get sprite batch: '{}'", name);
    try {
        return this->spriteBatches.at(name);
    } catch (...) {
        // TODO: make this work again, I've short circuited it.
        SpriteBatch *spriteBatch = 0;
        this->spriteBatches[name] = spriteBatch;
        return spriteBatch;
    }
}

sf::SoundBuffer *Repository::getSound(char const *name) {
    spdlog::info("get sound: '{}'", name);
    try {
        return this->sounds.at(name);
    } catch (...) {
        sf::SoundBuffer *sound = new sf::SoundBuffer();
        this->path.applyFolders(name);
        if (sound->loadFromFile(this->path.in(name))) {
            this->path.removeFolders(name);
            this->sounds[name] = sound;
            return sound;
        } else {
            spdlog::error("Cannot load sound at '{}'", this->path.in(name));
            throw -1;
        }
    }
}

sf::Music *Repository::getSong(char const *name) {
    spdlog::info("get song: '{}'", name);

}

Tileset const *Repository::getTileset(char const *name) {
    spdlog::info("Get tileset: '{}'", name);
    try {
        return this->tilesets.at(name);
    } catch(...) {
        pugi::xml_node node = this->readNode(name, "tileset");
        Tileset *tileset = new Tileset(node, this);
        this->tilesets[name] = tileset;
        return tileset;
    }
}

TileMap const *Repository::getTileMap(char const *name) {
    spdlog::info("Get tilemap: '{}'", name);
    try {
        return this->tileMaps.at(name);
    } catch (...) {
        this->path.applyFolders(name);
        pugi::xml_node node = this->readNode(this->path.in(name), "map");
        TileMap *tileMap = new TileMap(node, this);
        this->path.removeFolders(name);
        this->tileMaps[name] = tileMap;
        return tileMap;
    }
}

char const *Repository::getText(char const *name) {
    spdlog::info("get text: '{}'", name);
    try {
        return this->texts.at(name);
    } catch (...) {
        this->path.applyFolders(name);
        char *text = Utils::readFile(this->path.in(name));
        this->path.removeFolders(name);
        this->texts[name] = text;
        return text;
    }
}

sf::Font const *Repository::getFont() {
    spdlog::info("get font");
    return &this->font;
}

pugi::xml_node Repository::readNode(char const *name, char const *tag) {
    char const *text = this->getText(name);
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(text);
    if (!result) {
        spdlog::critical("'{}' is not a valid xml file", name);
        throw -1;
    }
    pugi::xml_node node = doc.child(tag);
    if (!node) {
        spdlog::critical("xml file '{}' lacks top level node '{}'", name, tag);
        throw -1;
    }
    return node;
}
