#include "Config.hh"
#include <string>
#include "spdlog/spdlog.h"
#include "inih.hh"

Config::Config(char const *file): Store(file) {
    spdlog::info("Loading config data from '{}'", file);
    // Load in flags.
    if (ini_parse(file, Config::handleIni, this) < 0) {
        spdlog::error("Could not open file '{}'", file);
        throw -1;
    }
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

int Config::handleIni(void *reference, char const *section, char const *name, char const *value) {
    spdlog::debug("Config value '{}': '{}'", name, value);
    char *newValue = new char[strlen(value)];
    strcpy(newValue, value);
    Config *config = (Config *)reference;
    config->store(name, newValue);
    return 1;
}
