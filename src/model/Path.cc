#include "model/Path.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <string.h>

Path::Path(char const *base, char const *file) {
    int baseEnd = strlen(base);
    while (base[baseEnd] != '/' && baseEnd > 0) baseEnd--;
    memcpy(this->buffer, base, baseEnd);
    int token = 0;
    int tokenStart = 0;
    int fileLength = strlen(file);
    while (token < fileLength) {
        tokenStart = token;
        token = Utils::pathToken(file + tokenStart);
        this->applyToken(file + tokenStart, token)

    }

}

char const *Path::get() {
    return this->buffer;
}

void Path::applyToken(char const *start, int length) {
    if (length == 2 && start[0] == '.' && start[1] == '.' && this->n > 0) {
        while (this->n > 0 && this->buffer[this->n] != '/') this->n--;
    } else {
        if (this->n + length >= Path::TEXT_BUFFER_SIZE) {
            length -= this->n + length - Path::TEXT_BUFFER_SIZE;
        }
        memcpy(this->buffer + this->n, start, length);
        this->n += length;
    }
    this->buffer[this->n] = 0;
}
