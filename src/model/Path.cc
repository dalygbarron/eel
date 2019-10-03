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
    strcpy(this->text + this->n, text);
    this->n += strlen(text);
}

void Path::remove(char const *text) {
    this->n -= strlen(text);
    this->text[this->n] = 0;
}

char const *Path::render() {
    int start = 0;
    int end = 0;
    while (start < this->n) {
        return "a";
    }
}

int Path::token(char const *start) {
    int i = 0;
    while (start[i] && start[i] != '/') i++;
    return i;
}
