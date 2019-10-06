#include "service/repository/TextRepository.hh"
#include "static/Utils.hh"

TextRepository::TextRepository(Config const *config) {
    this->config = config;
}

char const *TextRepository::create(char const *name) {
    spdlog::info("creating text: '{}'", name);
    char filename[Constant::FILENAME_BUFFER_SIZE];
    this->config->inRoot(filename, name);
    return Utils::readFile(filename);
}
