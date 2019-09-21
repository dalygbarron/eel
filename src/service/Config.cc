#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/rapidxml/rapidxml.hpp"
#include "static/spdlog/spdlog.h"
#include "service/Config.hh"
#include <string>

Config::Config(char const *filename) {
    spdlog::info("Load game config from '{}'", filename);
    char *data = Utils::readFile(filename);
    this->parseXml(data);
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

void Config::parseXml(char *data) {
    rapidxml::xml_document<> doc;
    try {
        doc.parse<0>(data);
    } catch (rapidxml::parse_error e) {
        spdlog::critical("parsing exception. should add the error message");
        throw -1;
    }
    rapidxml::xml_node<> *node = doc.first_node("game");
    for (rapidxml::xml_attribute<> *attr = node->first_attribute();
        attr; attr = attr->next_attribute()) {
        char *name = attr->name();
        char *value = attr->value();
        if (strcmp(name, NAME) == 0) {

        } else if (strcmp(name, VERSION) == 0) {

        } else if (strcmp(name, ENGINE) == 0) {

        } else if (strcmp(name, WIDTH) == 0) {
            
        } else if (strcmp(name, HEIGHT) == 0) {

        } else {
            spdlog::warn(
                "ignoring unknown game attribute '{}' => '{}'",
                name,
                value
            );
        }
        spdlog::info("'{}' => '{}'", attr->name(), attr->value());
    }
}
