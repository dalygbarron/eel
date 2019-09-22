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
}
