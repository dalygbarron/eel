#include "util.h"

float util_min(float a, float b) {
    if (a < b) return a;
    return b;
}

float util_max(float a, float b) {
    if (a > b) return a;
    return b;
}

int util_whitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}
