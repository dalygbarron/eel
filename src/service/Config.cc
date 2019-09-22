#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/xml/pugixml.hpp"
#include "service/Config.hh"
#include <string>

Config::Config(char const *filename) {
    spdlog::info("Load game config from '{}'", filename);
    this->parseXml(filename);
    // Save root directory where file was.
    // TODO: make some decent functions for directory arithmetic maybe. This
    //       probably doesn't work on windows.
    int directory = -1;
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == '/') directory = i;
    }
    this->root = new char[directory + 1];
    memcpy(this->root, filename, directory);
    this->root[directory] = 0;
    spdlog::info("Root is '{}'", this->root);
}

Config::~Config() {
    delete this->root;
    delete this->name;
    delete this->version;
}

char const *Config::getRoot() const {
    return this->root;
}

int Config::inRoot(char *buffer, char const *file) const {
    return sprintf(buffer, "%s/%s", this->root, file);
}

char const *Config::getName() const {
    return this->name;
}

char const *Config::getVersion() const {
    return this->version;
}

int Config::getEngineMajor() const {
    return this->engineMajor;
}

int Config::getEngineMinor() const {
    return this->engineMinor;
}

sf::Vector2i Config::getDimensions() const {
    return this->dimensions;
}

void Config::parseXml(char const *filename) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename);
    if (!result) {
        spdlog::critical(
            "Invalid XML in game file: {}",
            result.description()
        );
        throw -1;
    }
    // Set main attributes.
    pugi::xml_node game = doc.child("game");
    if (!game) {
        spdlog::critical("Game file lacks top level game object");
        throw -1;
    }
    this->name = Utils::moveString(game.attribute("name").value());
    this->version = Utils::moveString(game.attribute("version").value());
    int width = Utils::parseInt(game.attribute("width").value());
    int height = Utils::parseInt(game.attribute("height").value());
    int engine = Utils::parseInt(game.attribute("engine").value());
    this->dimensions = sf::Vector2i(width, height);
    this->engineMajor = (engine & 0xff00) >> 8;
    this->engineMinor = engine & 0xff;
    // Set options.
    pugi::xml_node opts = game.child("opts");
    if (opts) {
        for (pugi::xml_node opt = opts.child("opt"); opt; 
            opt = opt.next_sibling("opt")) {
            this->store(
                opt.attribute("name").value(),
                Utils::moveString(opt.attribute("value").value())
            );
        }
    }
}
