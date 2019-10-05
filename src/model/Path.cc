#include "model/Path.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <string.h>

Path::Path() {
    this->text[0] = 0;
    this->rendered[0] = 0;
    this->n = 0;
    this->rn = 0;
}

Path::Path(Path const *parent) {
    strcpy(this->text, parent->text);
    this->n = parent->n;
    this->rn = 0;
}

void Path::apply(char const *text) {
    if (this->n > 0 && this->text[this->n - 1] != '/') {
        this->text[this->n] = '/';
        this->n++;
    }
    strcpy(this->text + this->n, text);
    this->n += strlen(text);
    this->rn = 0;
}

void Path::applyFolders(char const *text) {
    if (this->n > 0 && this->text[this->n - 1] != '/') {
        this->text[this->n] = '/';
        this->n++;
    }
    int length = strlen(text);
    for (; length >= 0 && text[length] != '/'; length--);
    memcpy(this->text + this->n, text, length);
    this->n += length;
    this->text[this->n] = 0;
    this->rn = 0;
}

void Path::remove(char const *text) {
    this->n -= (strlen(text) + 1);
    this->text[this->n] = 0;
    this->rn = 0;
}

void Path::removeFolders(char const *text) {
    int length = strlen(text);
    for (; length > 0 && text[length] != '/'; length--);
    this->n -= length;
    if (this->n > 0) this->n -= 1;
    this->text[this->n] = 0;
    this->rn = 0;
}

char const *Path::render() {
    if (this->rn > 0) return this->rendered;
    int start = 0;
    int write = 0;
    int oldEnd = 0;
    while (start < this->n) {
        int end = Path::token(this->text + start);
        if (this->text[start + 1] == '.' && this->text[start + 2] == '.' &&
            end == 3) {
            write -= oldEnd;
            this->rendered[write] = 0;
        } else if (end > 0) {
            memcpy(this->rendered + write, this->text + start, end);
            write += end;
        }
        start += end;
        oldEnd = end;
    }
    this->rendered[write] = 0;
    this->rn = write;
    spdlog::error("rendered: '{}'", this->rendered);
    return this->rendered;
}

char const *Path::in(char const *file) {
    int length = strlen(file);
    for (; length >= 0 && file[length] != '/'; length--);
    this->render();
    strcpy(this->rendered + this->rn, file + length);
    spdlog::error("in'd: '{}'", this->rendered);
    return this->rendered;
}

char const *Path::inWhole(char const *file) {
    this->render();
    this->rendered[this->rn] = '/';
    strcpy(this->rendered + this->rn + 1, file);
    return this->rendered;
}

int Path::token(char const *start) {
    int i = 1;
    while (start[i] && start[i] != '/') i++;
    return i;
}
