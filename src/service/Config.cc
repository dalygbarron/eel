#include "service/Config.hh"
#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/xml/pugixml.hpp"
#include <string>

Config::Config(
    char const &name,
    char const &version,
    int engineMajor,
    int engineMinor,
    int width,
    int height
):
    name(&name),
    version(&version),
    engineMajor(engineMajor),
    engineMinor(engineMinor),
    dimensions(width, height)
{
    // does nothing else rn.
}

Config::~Config() {
    this->options.clear();
}

char const &Config::getOption(char const &name) const {
    if (this->options.count(&name) == 0) {
        throw new std::domain_error("No such option");
    }
    return *this->options.at(&name).c_str();
}

void Config::addOption(char const &name, char const &value) {
    this->options.emplace(&name, &value);
}

