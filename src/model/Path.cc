#include "model/Path.hh"
#include "static/Utils.hh"
#include <string.h>

Path::Path(char const *base, char const *file) {
    // Apply base text.
    int baseEnd = strlen(base);
    while (base[baseEnd] != '/' && baseEnd > 0) baseEnd--;
    baseEnd++;
    memcpy(this->buffer, base, baseEnd);
    this->n = baseEnd;
    if (this->buffer[this->n - 1] != '/') {
        this->buffer[this->n] = '/';
        this->n++;
    }
    this->buffer[this->n] = 0;
    // Apply tokens of extra text one by one.
    int token = 0;
    int tokenStart = 0;
    int fileLength = strlen(file);
    while (tokenStart < fileLength) {
        token = Utils::pathToken(file + tokenStart);
        this->applyToken(file + tokenStart, token);
        tokenStart += token;
    }
}

char const *Path::get() {
    return this->buffer;
}

void Path::applyToken(char const *start, int length) {
    // don't add initial slashes on added path.
    while (this->n != 0 && this->buffer[this->n - 1] == '/' &&
        length > 0 && start[0] == '/') {
        start++;
        length--;
    }
    // check for .. tokens.
    if (length == 2 && start[0] == '.' && start[1] == '.' && this->n > 1) {
        this->n -= 2;
        for(; this->n > 0 && this->buffer[this->n] != '/'; this->n--);
    } else {
        // Shorten if it will overrun buffer.
        if (this->n + length >= Path::TEXT_BUFFER_SIZE) {
            length -= this->n + length - Path::TEXT_BUFFER_SIZE;
        }
        // add token
        memcpy(this->buffer + this->n, start, length);
        this->n += length;
    }
    // null terminate new end of buffer
    this->buffer[this->n] = 0;
}
