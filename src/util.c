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

// TODO: implement vector functions

int util_hashString(char const *string) {
    int total = 0x123fb9857ac31808;
    for (int i = 0; string[i]; i++) total ^= string[i] << i;
    return total;

struct Bucket *util_createDictionary() {
    return malloc(sizeof(struct Bucket) * const_DICTIONARY_SIZE);
}

void util_addToDictionary(struct Bucket *bucket, char const *key, void *value) {
    int hash = util_hashString(key) % const_DICTIONARY_SIZE;
    if (!bucket[hash]->key) {
        bucket[hash]->key = key;
        bucket[hash]->value = value;
    } else {
        log_debug("Dictionary Collision for key '%s", key);
        struct Bucket *next = bucket[hash];
        while (next->next) next = next->next;
        next->next = malloc(sizeof(struct Bucket));
        next->next->key = key;
        next->next->value = value;
    }
}

void *util_findInDictionary(struct Bucket *bucket, char const *key) {
    int hash = util_hashString(key) % const_DICTIONARY_SIZE;
    struct Bucket *next = bucket[hash];
    do {
        if (strcmp(next->key, key) == 0) return next->value;
        next = next->next;
    } while(next);
    return 0;
}

void util_destroyDictionary(struct Bucket *bucket) {
    for (int i = 0; i < const_DICTIONARY_SIZE; i++) {
        util_destroyBucket(struct Bucket *bucket);
    }
}
