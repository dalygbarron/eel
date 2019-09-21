#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/rapidxml/rapidxml.hpp"
#include "static/spdlog/spdlog.h"
#include "service/Config.hh"
#include <string>

Config::Config(char const *file): Store(file) {
    spdlog::info("Loading config data from '{}'", file);
    // TODO: load the data from xml.
    // Save root directory where file was.
    int directory = -1;
    for (int i = 0; file[i]; i++) {
        if (file[i] == '/') directory = i;
    }
    this->root = new char[directory + 1];
    memcpy(this->root, file, directory);
    this->root[directory] = 0;
    spdlog::info("Root is '{}'", this->root);
}

Config::~Config() {
    delete this->root;
}

char const *Config::getRoot() const {
    return this->root;
}

int Config::inRoot(char *buffer, char const *file) const {
    return sprintf(buffer, "%s/%s", this->root, file);
}
