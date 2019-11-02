#include "service/repository/TextRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"

TextRepository::TextRepository(char const &root): Repository(root) {
    // does nothing.
}

char *TextRepository::create(char const &filename, char const &key) const {
    spdlog::info("creating text: '{}'", &filename);
    return &Utils::readFile(filename);
}
