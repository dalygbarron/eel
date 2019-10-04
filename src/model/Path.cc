#include "model/Path.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <string.h>

Path::Path() {
    text[0] = 0;
    rendered[0] = 0;
    n = 0;
}

Path::Path(Path const *parent) {
    strcpy(text, parent->text);
    n = parent->n;
}

void Path::apply(char const *text) {
    if (this->n > 0 && this->text[this->n - 1] != '/') {
        this->text[this->n] = '/';
        this->n++;
    }
    strcpy(this->text + this->n, text);
    this->n += strlen(text);
}

void Path::remove(char const *text) {
    this->n -= (strlen(text) + 1);
    this->text[this->n] = 0;
}

char const *Path::render() {
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
    spdlog::error("'{}'", this->rendered);
    return this->rendered;
}

int Path::token(char const *start) {
    int i = 1;
    while (start[i] && start[i] != '/') i++;
    return i;
}
