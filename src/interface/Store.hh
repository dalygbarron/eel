#ifndef STORE_H
#define STORE_H

#include "static/spdlog/spdlog.h"
#include <string>
#include <string.h>
#include <unordered_map>

/**
 * Generic storing thingy which stores stuff for example a store of config
 * strings, or a store of booleans.
 */
template <class T> class Store {
    public:
        /**
         * Gets a value from the configuration and if it's not found it throws
         * an exception and logs an error.
         * @param key is the key to the value to get.
         * @return the string value found.
         * @throws an exception and logs if it's not found. Meant to anyway.
         */
        T get(char const *key) const {
            try {
                return this->values.at(key);
            } catch (...) {
                spdlog::critical("Failed to find key '{}' in store", key);
                throw -1;
            }
        }

        /**
         * Gets a value from the configuration and if it's not found it returns
         * a default.
         * @param key is the key to the value to find.
         * @param net is the default value to return if the key doesn't exist.
         * @return the found value or the default if no found value.
         */
        T getSafely(char const *key, T net) const {
            try {
                return this->values.at(key);
            } catch (...) {
                return net;
            }
        }

        /**
         * Logs all the keys and values in the store.
         */
        void log() {
            for (std::pair<std::string, T> pair: this->values) {
                spdlog::debug("'{}' => '{}'", pair.first, pair.second);
            }
        }

    protected:
        /**
         * Add something into the store.
         * @param key   is the key under which the thing will be stored.
         * @param value is the value taht is being stored.
         */
        void store(char const *key, T value) {
            this->values[key] = value;
        }

    private:
        std::unordered_map<std::string, T> values;
};

#endif
