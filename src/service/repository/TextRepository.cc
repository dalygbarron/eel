#include "service/repository/TextRepository.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"

char const *TextRepository::create(char const *filename) {
    spdlog::info("creating text: '{}'", filename);
    return Utils::readFile(filename);
}
