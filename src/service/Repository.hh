#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "service/Config.hh"
#include "model/SpriteBatch.hh"
#include "model/Tileset.hh"
#include "model/TileMap.hh"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

/**
 * Loads assets out of files and then keeps them stored for later.
 * Could potentially add strategic dropping of little used data if memory 
 * usage is an issue but I doubt that.
 */
class Repository {
    public:
        template <class T> void addFactory(Factory<T> *factory) {
            std::type_index i = std::type_index(typeid(T));
            if (factories.contains(i)) {
                spdlog::error(
                    "Trying to add two factories of same type to repository"
                );
            } else {
                factories[i] = factory;
            }
        }

        template<typename T>
        bool addFactory( std::unique_ptr<ResourceFactory<T>> factory ) {
            std::type_index ti = std::type_index(typeid(T));

            auto searchResult = factories.find(ti);
            if(searchResult != factories.end()) {
                return false;
            } else {
                factories[ti] = std::move(factory);
                return true;
            }
        }

        template <typename T>
        ResourceHandle<T> load(const std::string &path) {
            std::type_index ti = std::type_index(typeid(T));
            auto searchResult = factories.find(ti);

            if(searchResult == factories.end()) {
                throw NoValidFactory(std::string("No registered factory of type ") +
                                     ti.name());
            }

            // TODO SOMEHOW DO LOADING
            //return searchResult->second->load(path);
        }

    private:
        /**
         * Loads in a cached text file then parses it as xml.
         * @param name is the name of the file to open the text from.
         * @param tag  is the type of top level node to seek and return.
         * @return the desired node always. if it fails it will crash the
         *         program.
         */
        pugi::xml_node readNode(char const *name, char const *tag);

        std::unordered_map<std::type_index, Factory *> factories;
};

#endif
