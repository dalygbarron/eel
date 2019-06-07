#include "Store.hh"

Store::Store(char const *name) {
    this->name = name;
}

T *Store::get(char const *key) const {
    try {
        return this->values.at(key);
    } catch (std::out_of_range const *e) {
        spdlog::error("Failed to find key '{}' in store '{}'", key, this->name);
        throw -1;
    }
}

T *Store::getSafely(char const *key, T default) const {
    try {
        return this->values.at(key);
    } catch (std::out_of_range const *e) {
        return default;
    }
}
