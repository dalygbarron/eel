#include "model/Path.hh"
#include "static/Utils.hh"
#include <string.h>

Path::Path(char const &base, char const &file) {
    char const *baseChars = &base;
    char const *fileChars = &file;
    // Apply base text.
    int baseEnd = strlen(baseChars);
    while (baseChars[baseEnd] != '/' && baseEnd > 0) baseEnd--;
    if (baseEnd > 0) baseEnd++;
    memcpy(this->buffer, baseChars, baseEnd);
    this->n = baseEnd;
    if (this->n > 0 && this->buffer[this->n - 1] != '/') {
        this->buffer[this->n] = '/';
        this->n++;
    }
    this->buffer[this->n] = 0;
    // Apply tokens of extra text one by one.
    int token = 0;
    int tokenStart = 0;
    int fileLength = strlen(fileChars);
    while (tokenStart < fileLength) {
        token = Utils::pathToken(*(fileChars + tokenStart));
        this->applyToken(fileChars + tokenStart, token);
        tokenStart += token;
    }
}

char const &Path::get() {
    return *this->buffer;
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
            length -= this->n + length - Path::TEXT_BUFFER_SIZE + 1;
        }
        // add token
        memcpy(this->buffer + this->n, start, length);
        this->n += length;
    }
    // null terminate new end of buffer
    this->buffer[this->n] = 0;
}
