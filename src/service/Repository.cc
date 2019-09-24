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
    this->config = config;
    char fontFile[Constant::FILENAME_BUFFER_SIZE];
    config->inRoot(fontFile, config->get("font"));
    if (!this->font.loadFromFile(fontFile)) {
        spdlog::critical("Could not load font from file '{}'", fontFile);
        throw -1;
    }
}

Repository::~Repository() {
    this->textures.clear();
    this->texts.clear();

}

sf::Texture *Repository::getTexture(char const *name) {
    spdlog::info("get texture: '{}'", name);
    try {
        return this->textures.at(name);
    } catch (...) {
        char filename[Constant::FILENAME_BUFFER_SIZE];
        this->config->inRoot(filename, name);
        sf::Texture *texture = new sf::Texture();
        if (!texture->loadFromFile(filename)) {
            spdlog::error("Cannot load texture at '{}'", filename);
        } else {
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
        char filename[Constant::FILENAME_BUFFER_SIZE];
        this->config->inRoot(filename, name);
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
        char filename[Constant::FILENAME_BUFFER_SIZE];
        this->config->inRoot(filename, name);
        sf::SoundBuffer *sound = new sf::SoundBuffer();
        if (sound->loadFromFile(filename)) {
            this->sounds[name] = sound;
            return sound;
        } else {
            spdlog::error("Cannot load sound at '{}'", filename);
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
        char const *data = this->getText(name);
        Tileset *tileset = new Tileset(data, this);
        this->tilesets[name] = tileset;
        return tileset;
    }
    
}

TileMap const *Repository::getTileMap(char const *name) {
    spdlog::info("Get tilemap: '{}'", name);
    try {
        return this->tileMaps.at(name);
    } catch (...) {
        char const *data = this->getText(name);
        TileMap *tileMap = new TileMap(data, this);
        this->tileMaps[name] = tileMap;
        return tileMap;
    }
}

char const *Repository::getText(char const *name) {
    spdlog::info("get text: '{}'", name);
    try {
        return this->texts.at(name);
    } catch (...) {
        char filename[Constant::FILENAME_BUFFER_SIZE];
        this->config->inRoot(filename, name);
        char *text = Utils::readFile(filename);
        this->texts[name] = text;
        return text;
    }
}

sf::Font const *Repository::getFont() {
    spdlog::info("get font");
    return &this->font;
}
